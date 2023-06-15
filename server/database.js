import mysql from "mysql2";
import dotenv from "dotenv";
dotenv.config();

const pool = mysql.createPool({
    host: process.env.MYSQL_HOST,
    user: process.env.MYSQL_USER,
    password: process.env.MYSQL_PASSWORD,
    database: "room_data"
}).promise();

export async function getAllTemperatureData() {
    const [rows] = await pool.query(`SELECT * FROM temp_data;`);
    return rows;
}

async function getTemperatureDataById(id) {
    const [rows] = await pool.query(`SELECT * FROM temp_data WHERE id = ?;`, [id]);
    return rows;
}

export async function setTemperatureData(temp_in, temp_out) {
    const d = new Date();
    const [result] = await pool.query(`
    INSERT INTO temp_data (temp_in, temp_out, timestamp)
    VALUES (?, ?, ?);
    `, [temp_in, temp_out, new Date(d.getTime() - d.getTimezoneOffset() * 60 * 1000).toISOString().slice(0, 19).replace('T', ' ')]);
    return getTemperatureDataById(result.insertId);
}

export async function getDesiredTemperature() {
    const [rows] = await pool.query(`SELECT * FROM desired_temp;`);
    return rows[0];
}

export async function setDesiredTemperature(temp) {
    const [result] = await pool.query(`
    UPDATE desired_temp
    SET desired_temp = ?
    WHERE id = 1;
    `, [temp]);
    return getDesiredTemperature();
}