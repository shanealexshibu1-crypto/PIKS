#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <PS2X_lib.h>
#include <math.h>

Adafruit_PWMServoDriver leftDriver  = Adafruit_PWMServoDriver(0x40);
Adafruit_PWMServoDriver rightDriver = Adafruit_PWMServoDriver(0x41);

PS2X ps2x;

#define PS2_DAT 22
#define PS2_CMD 23
#define PS2_ATT 24
#define PS2_CLK 25

int ps2Error = 0;

const float COXA_LENGTH  = 87.5;
const float FEMUR_LENGTH = 110.0;
const float TIBIA_LENGTH = 220.0;

#define SERVO_FREQ 50

const int SERVO_MIN_US = 500;
const int SERVO_MAX_US = 2500;

enum LegID
{
    LF = 0,
    LM = 1,
    LR = 2,
    RF = 3,
    RM = 4,
    RR = 5
};

enum JointID
{
    COXA = 0,
    FEMUR = 1,
    TIBIA = 2
};

struct ServoCalibration
{
    float center;
    float offset;
    int direction;
    float minAngle;
    float maxAngle;
};

ServoCalibration LF_Coxa  = {90, 0, +1, 5, 175};
ServoCalibration LF_Femur = {90, 0, +1, 5, 175};
ServoCalibration LF_Tibia = {115, 0, +1, 5, 175};

ServoCalibration LM_Coxa  = {90, 0, +1, 5, 175};
ServoCalibration LM_Femur = {90, 0, +1, 5, 175};
ServoCalibration LM_Tibia = {115, 0, +1, 5, 175};

ServoCalibration LR_Coxa  = {90, 0, +1, 5, 175};
ServoCalibration LR_Femur = {90, 0, +1, 5, 175};
ServoCalibration LR_Tibia = {115, 0, +1, 5, 175};


ServoCalibration RF_Coxa  = {90, 0, -1, 5, 175};
ServoCalibration RF_Femur = {90, 0, -1, 5, 175};
ServoCalibration RF_Tibia = {115, 0, -1, 5, 175};

ServoCalibration RM_Coxa  = {90, 0, -1, 5, 175};
ServoCalibration RM_Femur = {90, 0, -1, 5, 175};
ServoCalibration RM_Tibia = {115, 0, -1, 5, 175};

ServoCalibration RR_Coxa  = {90, 0, -1, 5, 175};
ServoCalibration RR_Femur = {90, 0, -1, 5, 175};
ServoCalibration RR_Tibia = {115, 0, -1, 5, 175};

struct LegPosition
{
    float x;
    float y;
    float z;
};

LegPosition foot[6];

const float STAND_X_FRONT = 150.0;
const float STAND_X_MIDDLE = 0.0;
const float STAND_X_REAR = -150.0;

const float STAND_Y = 145.0;

float bodyHeight = -170.0;

float moveX = 0;
float moveY = 0;
float rotation = 0;


const float MAX_FORWARD = 80.0;
const float MAX_STRAFE  = 60.0;
const float MAX_ROTATE  = 45.0;

const unsigned long GAIT_PERIOD = 700;

const float STEP_HEIGHT = 55.0;

float cubicBezier(float p0, float p1, float p2, float p3, float t)
{
    float u = 1.0 - t;

    return
        (u * u * u * p0) +
        (3.0 * u * u * t * p1) +
        (3.0 * u * t * t * p2) +
        (t * t * t * p3);
}

uint16_t microsecondsToTicks(int us)
{
    
    return (uint16_t)((us * 4096.0) / 20000.0);
}


void writeServoPWM(bool rightSide, int channel, float angle)
{
    angle = constrain(angle, 0, 180);

    int pulse =
        SERVO_MIN_US +
        ((SERVO_MAX_US - SERVO_MIN_US) * angle / 180.0);

    uint16_t ticks = microsecondsToTicks(pulse);

    if (rightSide)
        rightDriver.setPWM(channel, 0, ticks);
    else
        leftDriver.setPWM(channel, 0, ticks);
}

float calibratedAngle(ServoCalibration &servo, float ikAngle)
{
    float result =
        servo.center +
        servo.offset +
        servo.direction * ikAngle;

    result = constrain(
        result,
        servo.minAngle,
        servo.maxAngle
    );

    return result;
}

ServoCalibration* getCalibration(int leg, int joint)
{
    if (leg == LF)
    {
        if (joint == COXA)  return &LF_Coxa;
        if (joint == FEMUR) return &LF_Femur;
        return &LF_Tibia;
    }

    if (leg == LM)
    {
        if (joint == COXA)  return &LM_Coxa;
        if (joint == FEMUR) return &LM_Femur;
        return &LM_Tibia;
    }

    if (leg == LR)
    {
        if (joint == COXA)  return &LR_Coxa;
        if (joint == FEMUR) return &LR_Femur;
        return &LR_Tibia;
    }

    if (leg == RF)
    {
        if (joint == COXA)  return &RF_Coxa;
        if (joint == FEMUR) return &RF_Femur;
        return &RF_Tibia;
    }

    if (leg == RM)
    {
        if (joint == COXA)  return &RM_Coxa;
        if (joint == FEMUR) return &RM_Femur;
        return &RM_Tibia;
    }

    // RR
    if (joint == COXA)  return &RR_Coxa;
    if (joint == FEMUR) return &RR_Femur;
    return &RR_Tibia;
}

int getServoChannel(int leg, int joint)
{
    if (leg <= LR)
    {
        // LEFT
        return leg * 3 + joint;
    }
    else
    {
        // RIGHT
        return (leg - 3) * 3 + joint;
    }
}

bool solveIK(
    float x,
    float y,
    float z,
    float &coxaAngle,
    float &femurAngle,
    float &tibiaAngle
)
{
    coxaAngle = atan2(y, x) * 180.0 / PI;

    float horizontal =
        sqrt((x * x) + (y * y));

    float r =
        horizontal - COXA_LENGTH;


    float distance =
        sqrt((r * r) + (z * z));



    if (distance > FEMUR_LENGTH + TIBIA_LENGTH)
        return false;

    if (distance < fabs(FEMUR_LENGTH - TIBIA_LENGTH))
        return false;


    float cosTibia =
        (
            (FEMUR_LENGTH * FEMUR_LENGTH) +
            (TIBIA_LENGTH * TIBIA_LENGTH) -
            (distance * distance)
        )
        /
        (
            2.0 *
            FEMUR_LENGTH *
            TIBIA_LENGTH
        );

    cosTibia = constrain(cosTibia, -1.0, 1.0);

    float tibiaRad =
        acos(cosTibia);

    tibiaAngle =
        tibiaRad * 180.0 / PI;

    float angleToFoot =
        atan2(z, r);

    float cosFemur =
        (
            (FEMUR_LENGTH * FEMUR_LENGTH) +
            (distance * distance) -
            (TIBIA_LENGTH * TIBIA_LENGTH)
        )
        /
        (
            2.0 *
            FEMUR_LENGTH *
            distance
        );

    cosFemur = constrain(cosFemur, -1.0, 1.0);

    float triangleAngle =
        acos(cosFemur);

    float femurRad =
        angleToFoot + triangleAngle;

    femurAngle =
        femurRad * 180.0 / PI;

    coxaAngle += 90.0;

    femurAngle = 90.0 - femurAngle;

    tibiaAngle = tibiaAngle;


    return true;
}

void moveLeg(
    int leg,
    float x,
    float y,
    float z
)
{
    float coxa;
    float femur;
    float tibia;

    bool valid =
        solveIK(
            x,
            y,
            z,
            coxa,
            femur,
            tibia
        );

    if (!valid)
        return;


    ServoCalibration *sCoxa =
        getCalibration(leg, COXA);

    ServoCalibration *sFemur =
        getCalibration(leg, FEMUR);

    ServoCalibration *sTibia =
        getCalibration(leg, TIBIA);


    float servoCoxa =
        calibratedAngle(*sCoxa, coxa);

    float servoFemur =
        calibratedAngle(*sFemur, femur);

    float servoTibia =
        calibratedAngle(*sTibia, tibia);


    bool rightSide =
        (leg >= RF);

    int channelCoxa =
        getServoChannel(leg, COXA);

    int channelFemur =
        getServoChannel(leg, FEMUR);

    int channelTibia =
        getServoChannel(leg, TIBIA);


    writeServoPWM(
        rightSide,
        channelCoxa,
        servoCoxa
    );

    writeServoPWM(
        rightSide,
        channelFemur,
        servoFemur
    );

    writeServoPWM(
        rightSide,
        channelTibia,
        servoTibia
    );
}

void calculateStandPositions()
{
    
    foot[LF] = {
        STAND_X_FRONT,
        +STAND_Y,
        bodyHeight
    };

    foot[LM] = {
        STAND_X_MIDDLE,
        +STAND_Y,
        bodyHeight
    };

    foot[LR] = {
        STAND_X_REAR,
        +STAND_Y,
        bodyHeight
    };

    foot[RF] = {
        STAND_X_FRONT,
        -STAND_Y,
        bodyHeight
    };

    foot[RM] = {
        STAND_X_MIDDLE,
        -STAND_Y,
        bodyHeight
    };

    foot[RR] = {
        STAND_X_REAR,
        -STAND_Y,
        bodyHeight
    };
}



void stand()
{
    calculateStandPositions();

    for (int leg = 0; leg < 6; leg++)
    {
        moveLeg(
            leg,
            foot[leg].x,
            foot[leg].y,
            foot[leg].z
        );
    }
}

bool isTripodA(int leg)
{
    return
        leg == LF ||
        leg == RM ||
        leg == LR;
}

void applyRotation(
    float x,
    float y,
    float rotationAmount,
    float &outX,
    float &outY
)
{
    float rot =
        rotationAmount * PI / 180.0;

    outX =
        x * cos(rot) -
        y * sin(rot);

    outY =
        x * sin(rot) +
        y * cos(rot);
}

void updateGait()
{
    unsigned long now = millis();

    float cycle =
        (now % GAIT_PERIOD) /
        (float)GAIT_PERIOD;

    float stepX =
        moveX;

    float stepY =
        moveY;

    for (int leg = 0; leg < 6; leg++)
    {
        bool tripodA =
            isTripodA(leg);

        float phase =
            cycle;

        if (!tripodA)
            phase += 0.5;

        if (phase >= 1.0)
            phase -= 1.0;


        float x =
            foot[leg].x;

        float y =
            foot[leg].y;

        float z =
            foot[leg].z;

        if (phase < 0.5)
        {
            float t =
                phase / 0.5;

            float startX =
                x - stepX * 0.5;

            float endX =
                x + stepX * 0.5;


            float startY =
                y - stepY * 0.5;

            float endY =
                y + stepY * 0.5;


            float control1X =
                startX + stepX * 0.25;

            float control2X =
                endX - stepX * 0.25;


            float control1Y =
                startY + stepY * 0.25;

            float control2Y =
                endY - stepY * 0.25;


            float targetX =
                cubicBezier(
                    startX,
                    control1X,
                    control2X,
                    endX,
                    t
                );

            float targetY =
                cubicBezier(
                    startY,
                    control1Y,
                    control2Y,
                    endY,
                    t
                );


            float targetZ =
                cubicBezier(
                    z,
                    z - STEP_HEIGHT,
                    z - STEP_HEIGHT,
                    z,
                    t
                );


            float rotatedX;
            float rotatedY;

            applyRotation(
                targetX,
                targetY,
                rotation,
                rotatedX,
                rotatedY
            );


            moveLeg(
                leg,
                rotatedX,
                rotatedY,
                targetZ
            );
        }

        else
        {
            float t =
                (phase - 0.5) / 0.5;

            float targetX =
                x + stepX * 0.5 -
                stepX * t;

            float targetY =
                y + stepY * 0.5 -
                stepY * t;


            float rotatedX;
            float rotatedY;

            applyRotation(
                targetX,
                targetY,
                rotation,
                rotatedX,
                rotatedY
            );


            moveLeg(
                leg,
                rotatedX,
                rotatedY,
                z
            );
        }
    }
}

int applyDeadzone(
    int value,
    int deadzone
)
{
    if (abs(value) < deadzone)
        return 0;

    return value;
}

float stickToFloat(
    int value,
    float maximum
)
{
    value -= 128;

    value =
        applyDeadzone(
            value,
            15
        );

    if (value == 0)
        return 0;

    float normalized =
        value / 127.0;

    return normalized * maximum;
}

void readController()
{
    ps2x.read_gamepad(
        false,
        0
    );

    int leftX =
        ps2x.Analog(PSS_LX);

    int leftY =
        ps2x.Analog(PSS_LY);

    int rightX =
        ps2x.Analog(PSS_RX);

    int rightY =
        ps2x.Analog(PSS_RY);

    moveY =
        -stickToFloat(
            leftX,
            MAX_STRAFE
        );

    moveX =
        -stickToFloat(
            leftY,
            MAX_FORWARD
        );

    rotation =
        -stickToFloat(
            rightX,
            MAX_ROTATE
        );

    float heightChange =
        stickToFloat(
            rightY,
            1.0
        );


    bodyHeight +=
        heightChange * 3.0;


    bodyHeight =
        constrain(
            bodyHeight,
            -220.0,
            -120.0
        );


    static bool lastStart = false;

    bool startPressed =
        ps2x.ButtonPressed(PSB_START);

    if (startPressed && !lastStart)
    {
        stand();
    }

    lastStart =
        startPressed;
}


void setupPS2()
{
    delay(300);

    ps2Error =
        ps2x.config_gamepad(
            PS2_CLK,
            PS2_CMD,
            PS2_ATT,
            PS2_DAT,
            false,
            false
        );

    if (ps2Error == 0)
    {
        Serial.println(
            "PS2 controller connected."
        );
    }
    else
    {
        Serial.print(
            "PS2 controller error: "
        );

        Serial.println(ps2Error);
    }
}


void setup()
{
    Serial.begin(115200);

    Wire.begin();

    leftDriver.begin();
    rightDriver.begin();

    leftDriver.setOscillatorFrequency(27000000);
    rightDriver.setOscillatorFrequency(27000000);

    leftDriver.setPWMFreq(SERVO_FREQ);
    rightDriver.setPWMFreq(SERVO_FREQ);


    delay(500);


    setupPS2();

    calculateStandPositions();


    stand();


    Serial.println(
        "HEXAPOD READY"
    );
}

void loop()
{
    readController();

    updateGait();

    delay(15);
}