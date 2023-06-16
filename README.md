# SmartWindow project
## Course work for 4th term on IoT program in LPNU

**NodeMCU ESP8266** microcontroller is used to collect temperature data and transfer it to the database via backend server.
Servo motor is used to open and close the window.
Desired temperature is recieved by the microcontroller from the database, and can be changed by the user via frontend.

Frontend is written in **React.js**, backend in **Node.js**, database is **MySQL**.

## How to run
1. Assemble the circuit according to the scheme
2. Create a database using the `database.sql` file
3. Clone the repository
4. Connect NodeMCU to your computer and upload the code from `SmartWin.ino` file to it
5. Run `npm install` in both frontend and backend folders
6. Run `npm start` in both frontend and backend folders
7. Open `localhost:3000` in your browser

📁 In the `assets` folder you can find the video of the project in action as well as some photos of the circuit and the project itself.
<br />
<br />
### ⚠️ Warning: the Proteus scheme haven't been tested as the project was assembled on the real hardware. It may need some tweaking to work properly. On the real microcontroller the project works as intended.
