import axios from "axios";

const API_URL = "http://192.168.0.102:8000";

export const getAllTemperatureData = async () => {
    let temp_data = await axios.get(`${API_URL}/temp_data/`).then((response) => {
        return response.data;
    })
    .catch((error) => {
        console.log(error);
    });
    return temp_data;
}

export const getDesiredTemperature = async () => {
    let desired_temp = await axios.get(`${API_URL}/desired_temp/`).then((response) => {
        return response.data;
    })
    .catch((error) => {
        console.log(error);
    });
    return desired_temp;
}

export const setDesiredTemperature = async (temp) => {
    let desired_temp = await axios.post(`${API_URL}/desired_temp/`, null, {
        params: {
            temp: temp
        }
    }).then((response) => {
        return response.data;
    })
    .catch((error) => {
        console.log(error);
    });
    return desired_temp;
}