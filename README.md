# PIXS

Pixs is a 6 legged hexapod with 3-dof per leg i.e a hexapod with 18-dof. Custom made with a final volume box of 32 cm x 19.2 xm x 29.1 cm



## Printing Parts

Material used is PET-G

| Setting                |  value |
| ---------------------- | ------------------: |
| **Nozzle**             |           **240°C** |
| **Bed**                |            **80°C** |
| **Part cooling**       |          **30–50%** |
| **Print speed**        |      **40–60 mm/s** |
| **First-layer nozzle** |           **245°C** |
| **First-layer bed**    |            **80°C** |
| **Infill**             |          **10-15%** |

## Assembly

1. Print 6 copies of Coxa Link 1_Part1, Coxa link 1_Part 2, Coxa Link 2_Part 1, Coxa Link 2_Part 2, Femur Part 1, Femur Part 2, Tibia, Servo Mount Coxa Bottom, Servo Mount Coxa Middle
   ,Servo Mount Coxa Top, Servo Mount Femur Bottom, Servo Mount Femur Middle,Servo Mount Femur Top, Servo Mount Tibia Bottom, Servo Mount Tibia Middle, Servo Mount Tibia Top.
   
2. Print 1 copy of Body Base and Body Top.

3. Insert One 606zz Ball Bearings into all 18 bottom of the servo mounts.

4. Then attach the Middle and top attachments of the Servo Mount. Secure this with 4pcs 45mm m3 Screw and heated inserts

5. Attach the Servo Horns that come with the Servo to all the servos.

6. Combine Coxa Link 1_Part 1 , Coxa Link 1_Part 2 and Coxa Servo Joint. Secure this with 3 pcs of m3 x 10mm screws and heated inserts.Repeat this 6 times.

7. Combine Coxa Link 2_Part 1, Coxa Link 2_Part 2 and Femur Servo Joint. Secure this with 3pcs of m3 x 10mm Screwa and heated inserts. Repeat this 6 times.

8. Combine the products from step 6 and step 7  using 5 pcs of m3x15mm Screws and heated inserts.Repeat this 6 times.

9. Attach the Femur Part 1 , femur Part 2, Tibia servo joint with m3 x 10mm screws and heated inserts.Repeat 6 times.

10. combine the femur with the product from step 8 with m3 x 10mm screws and heated inserts.Repeat 6 times.

11. finally cominbe the tibia and the product from step 10 with m3x10mm screws.Repeat 6 times.

12. Now you have finished 6 legs.

13. Next take the legs and securthem in the designated spots with m3 x 10 mm screws. Repeat this 6 times.

14. Now u have a finished Assembled hexapod.


## Circuit Diagram

<img width="1634" height="813" alt="Screenshot 2026-09-01 at 8 35 06 PM" src="https://github.com/user-attachments/assets/8cabc633-a545-4dae-bd83-be9735f52ece" />

## Gallery

### One of the Finished Servo Mount

<img width="711" height="739" alt="Screenshot 2026-09-01 at 5 22 45 PM" src="https://github.com/user-attachments/assets/5c78f2e9-20a7-4889-9066-00b9b4e4fbd3" />

### Finished Leg Side View

<img width="863" height="654" alt="Screenshot 2026-09-01 at 5 24 09 PM" src="https://github.com/user-attachments/assets/1820d847-b7ed-40ce-92f7-9675c67d3e37" />

### Base Plate(Body)

<img width="1276" height="611" alt="Screenshot 2026-09-01 at 5 28 04 PM" src="https://github.com/user-attachments/assets/222c6aee-7a26-47d9-afcb-0d8cfeed385a" />

### Fully assembled Hexapod(Front View)

<img width="862" height="649" alt="Screenshot 2026-09-01 at 5 33 56 PM" src="https://github.com/user-attachments/assets/9723bb3d-ddad-48d9-87de-6d28948ebb3a" />


### Fully assembled Hexapod(Side View)

<img width="1045" height="669" alt="Screenshot 2026-09-01 at 5 34 15 PM" src="https://github.com/user-attachments/assets/98e0133d-c1bf-4cfd-9c07-b1b12848a07d" />


### Fully assembled Hexapod(Top View)

<img width="697" height="705" alt="Screenshot 2026-09-01 at 5 34 48 PM" src="https://github.com/user-attachments/assets/78eedcc6-e506-414b-bed8-b90b90fa95d9" />



## Firmware 

### Features:

1. The firmware uses a tripod gait that follows the bezier curve.
2. Uses a 3rd party PS2 style controller to control the Hexapod, Left joystick for movement and right joystick for rotation and height adjustment.

### Installation

  1.Download the latest version of Arduino IDE
  
  2.Download the firmware from my github repo.
  
  3.Open the firmware with Arduino IDE.
  
  4.Connect the Arduino Mega to the laptop via Usb Cable.
  
  5.Finally, verify and upload the code to the Mega.
  
  6.Enjoy a fully working Hexapod.



## BOM

|Part Name                 |Qty|Pcs per Qty|Cost (AED)|Purchase Place|Purchase Link|
|--------------------------|---|-----------|----------|--------------|-------------|
|Breadboard                |1  |1          |2.68      |Ali Express   |[Link](https://ar.aliexpress.com/item/1005009010052772.html?spm=a2g0o.cart.0.0.4d1438daw9M3Av&mp=1&pdp_npi=6%40dis%21AED%21AED+3.15%21AED+2.68%21%21AED+2.68%21%21%21%400bafc98f17882048086372500e0fb3%2112000047569744931%21ct%21AE%216327129338%21%211%210%21&gatewayAdapt=glo2ara)         |
|LiPo Battery              |1  |1          |79.11     |Ali Express   |[Link](https://ar.aliexpress.com/item/1005011908692707.html?spm=a2g0o.cart.0.0.4d1438daw9M3Av&mp=1&pdp_npi=6%40dis%21AED%21AED+131.85%21AED+79.11%21%21AED+79.11%21%21%21%400bafc98f17882048086372500e0fb3%2112000056980306680%21ct%21AE%216327129338%21%211%210%21&gatewayAdapt=glo2ara)         |
|M3 Screw 15mm             |15 |10         |3.69      |Ali Express   |[Link](https://ar.aliexpress.com/item/1005008693358029.html?spm=a2g0o.cart.0.0.4d1438daw9M3Av&mp=1&pdp_npi=6%40dis%21AED%21AED+5.28%21AED+3.69%21%21AED+3.38%21%21%21%400bafc98f17882048086372500e0fb3%2112000046269536251%21ct%21AE%216327129338%21%2115%210%21&gatewayAdapt=glo2ara)         |
|M3 Screw 10mm             |20 |10         |3.36      |Ali Express   |[Link](https://ar.aliexpress.com/item/1005008693358029.html?spm=a2g0o.cart.0.0.4d1438daw9M3Av&mp=1&pdp_npi=6%40dis%21AED%21AED+4.80%21AED+3.36%21%21AED+3.08%21%21%21%400bafc98f17882048086372500e0fb3%2112000046269536248%21ct%21AE%216327129338%21%2120%210%21&gatewayAdapt=glo2ara)         |
|Jumper Wires              |1  |1          |12.39     |Ali Express   |[Link](https://ar.aliexpress.com/item/1005012273851640.html?spm=a2g0o.cart.0.0.4d1438daiBjTQn&mp=1&pdp_npi=6%40dis%21AED%21AED+26.36%21AED+12.39%21%21AED+12.39%21%21%21%4021413b0b17882055110051546e0f96%2112000057938655893%21ct%21AE%216327129338%21%211%210%21&gatewayAdapt=glo2ara)         |
|Capacitors 6.3 V (1000 uF)|1  |20         |9.7       |Ali Express   |[Link](https://ar.aliexpress.com/item/1005006186858370.html?spm=a2g0o.cart.0.0.4d1438daiBjTQn&mp=1&pdp_npi=6%40dis%21AED%21AED+13.93%21AED+9.70%21%21AED+9.70%21%21%21%4021413b0b17882055110051546e0f96%2112000036215265922%21ct%21AE%216327129338%21%211%210%21&gatewayAdapt=glo2ara)         |
|LED Toggle Switch         |1  |1          |27.03     |Ali Express   |[Link](https://ar.aliexpress.com/item/1005008856506094.html?spm=a2g0o.cart.0.0.4d1438daiBjTQn&mp=1&pdp_npi=6%40dis%21AED%21AED+27.03%21AED+27.03%21%21AED+27.03%21%21%21%4021413b0b17882055110051546e0f96%2112000046963609399%21ct%21AE%216327129338%21%211%210%21&gatewayAdapt=glo2ara)         |
|Servo Extentions          |1  |15         |26.42     |Ali Express   |[Link](https://ar.aliexpress.com/item/1005010660995814.html?spm=a2g0o.cart.0.0.4d1438daiBjTQn&mp=1&pdp_npi=6%40dis%21AED%21AED+73.48%21AED+33.80%21%21AED+33.80%21%21%21%4021413b0b17882055110051546e0f96%2112000053107917571%21ct%21AE%216327129338%21%211%210%21&gatewayAdapt=glo2ara)         |
|5V 15A Regulator          |1  |1          |50.39     |Ali Express   |[Link](https://ar.aliexpress.com/item/1005010218924050.html?spm=a2g0o.cart.0.0.4d1438daiBjTQn&mp=1&pdp_npi=6%40dis%21AED%21AED+104.98%21AED+50.39%21%21AED+50.39%21%21%21%4021413b0b17882055110051546e0f96%2112000051565730974%21ct%21AE%216327129338%21%211%210%21&gatewayAdapt=glo2ara)         |
|DIN7991 M3 × 45mm Bolts   |1  |50         |25.47     |Ali Express   |[Link](https://ar.aliexpress.com/item/1005012615504199.html?spm=a2g0o.cart.0.0.4d1438daiBjTQn&mp=1&pdp_npi=6%40dis%21AED%21AED+25.73%21AED+25.73%21%21AED+25.73%21%21%21%4021413b0b17882055110051546e0f96%2112000058860258201%21ct%21AE%216327129338%21%211%210%21&gatewayAdapt=glo2ara)         |
|DIN7991 M3 × 45mm Bolts   |1  |50         |25.29     |Ali Express   |[Link](https://ar.aliexpress.com/item/1005012779784744.html?spm=a2g0o.cart.0.0.4d1438daiBjTQn&mp=1&pdp_npi=6%40dis%21AED%21AED+25.73%21AED+25.29%21%21AED+25.29%21%21%21%4021413b0b17882055110051546e0f96%2112000059335034318%21ct%21AE%216327129338%21%211%210%21&gatewayAdapt=glo2ara)         |
|PCA9685 Servo Driver      |1  |2          |26.83     |Ali Express   |[Link](https://ar.aliexpress.com/item/1005008717177681.html?spm=a2g0o.cart.0.0.4d1438daiBjTQn&mp=1&pdp_npi=6%40dis%21AED%21AED+26.83%21AED+4.16%21%21AED+4.16%21%21%21%4021413b0b17882055110051546e0f96%2112000046371071935%21ct%21AE%216327129338%21%211%210%21&gatewayAdapt=glo2ara)         |
|Wireless Controller       |1  |1          |42.2      |Ali Express   |[Link](https://ar.aliexpress.com/item/1005012464305134.html?spm=a2g0o.cart.0.0.4d1438daiBjTQn&mp=1&pdp_npi=6%40dis%21AED%21AED+42.20%21AED+42.20%21%21AED+42.20%21%21%21%4021413b0b17882055110051546e0f96%2112000058555043167%21ct%21AE%216327129338%21%211%210%21&gatewayAdapt=glo2ara)         |
|MEGA2560 R3               |1  |1          |61.57     |Ali Express   |[Link](https://ar.aliexpress.com/item/1005008973924627.html?spm=a2g0o.cart.0.0.4d1438daiBjTQn&mp=1&pdp_npi=6%40dis%21AED%21AED+61.57%21AED+61.57%21%21AED+61.57%21%21%21%4021413b0b17882055110051546e0f96%2112000047424332230%21ct%21AE%216327129338%21%211%210%21&gatewayAdapt=glo2ara)         |
|MG996 Servo               |18 |1          |16.31     |Ali Express   |[Link](https://ar.aliexpress.com/item/1005001878275044.html?spm=a2g0o.cart.0.0.4d1438daiBjTQn&mp=1&pdp_npi=6%40dis%21AED%21AED+16.31%21AED+16.31%21%21AED+16.31%21%21%21%4021413b0b17882055110051546e0f96%2112000017995190710%21ct%21AE%216327129338%21%2118%210%21&gatewayAdapt=glo2ara)         |
|Ball Bearing              |2  |10         |28        |Ali Express   |[Link](https://ar.aliexpress.com/item/560944845.html?spm=a2g0o.productlist.main.5.25803d28go3NlK&algo_pvid=5cf328c5-27c4-444b-a83b-2847f956face&algo_exp_id=5cf328c5-27c4-444b-a83b-2847f956face-4&pdp_ext_f=%7B%22order%22%3A%22103%22%2C%22spu_best_type%22%3A%22price%22%2C%22eval%22%3A%221%22%2C%22fromPage%22%3A%22search%22%7D&pdp_npi=6%40dis%21AED%2128.00%2128.00%21%21%217.40%217.40%21%402102eb1417882075531957530e0df0%2112000020777670370%21sea%21AE%216327129338%21ABX%211%210%21n_tag%3A-29910%3Bd%3A92a1c79a%3Bm03_new_user%3A-29895&curPageLogUid=WHP7pWYI5Soi&utparam-url=scene%3Asearch%7Cquery_from%3A%7Cx_object_id%3A560944845%7C_p_origin_prod%3A)         |
|Heated inserts            |4  |100        |16.96     |Ali Express   |[Link](https://ar.aliexpress.com/item/1005006201944599.html?spm=a2g0o.detail.0.0.d993ZfTrZfTrsQ&mp=1&pdp_npi=6%40dis%21AED%21AED+16.96%21AED+16.96%21%21AED+16.96%21%21%21%4021413b0b17882053640377287e0f96%2112000036250301739%21ct%21AE%216327129338%21%214%210%21&gatewayAdapt=glo2ara)         |
|                          |   |           |          |              |             |
|                          |   |TOTAL:     |457.4 AED |              |             |
