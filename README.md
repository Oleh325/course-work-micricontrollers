# SmartWindow project
## Course work for 4th term on IoT program in LPNU

**NodeMCU ESP8266** microcontroller is used to collect temperature data and transfer it to the database via backend server.
Servo motor is used to open and close the window.
Desired temperature is recieved by the microcontroller from the database, and can be changed by the user via frontend.

Frontend is written in **React.js**, backend in **Node.js**, database is **MySQL**.

## How to run
1. Assemble the circuit according to the scheme
2. Clone the repository
3. Create a database using the `database.sql` file
4. Create `server/.env` file and add the following lines to it:
```sql
MYSQL_HOST="your_host_here"
MYSQL_USER="your_username_here"
MYSQL_PASSWORD="your_password_here"
```
5. Create `SmartWin/wifi_data.h` file and add the following lines to it:
```cpp
#define SSID "name_of_your_wifi_here"
#define WIFI_PASSWORD "password_of_your_wifi_here"
```
6. Connect NodeMCU to your computer and upload the code from `SmartWin.ino` file to it
7. Run `npm install` in both frontend and backend folders
8. Run `npm start` in both frontend and backend folders
9. Open `localhost:3000` in your browser

📁 In the `assets` folder you can find the video of the project in action as well as some photos of the circuit and the project itself.
<br />
<br />
### ⚠️ Warning: the Proteus scheme haven't been tested as the project was assembled on the real hardware. It may need some tweaking to work properly. On the real microcontroller the project works as intended.
