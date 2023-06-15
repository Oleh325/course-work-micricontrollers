import axios from "axios";

export const getAllTemperatureData = async () => {
    let temp_data = await axios.get(`http://localhost:8080/temp_data/`).then((response) => {
        return response.data;
    })
    .catch((error) => {
        console.log(error);
    });
    return temp_data;
}

export const getDesiredTemperature = async () => {
    let desired_temp = await axios.get(`http://localhost:8080/desired_temp/`).then((response) => {
        return response.data;
    })
    .catch((error) => {
        console.log(error);
    });
    return desired_temp;
}

export const setDesiredTemperature = async (temp) => {
    let desired_temp = await axios.post(`http://localhost:8080/desired_temp/`, null, {
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