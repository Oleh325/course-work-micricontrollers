import { useEffect, useState } from 'react';
import { AppContainer, TemperatureInfo } from './App.styled';
import { getAllTemperatureData, getDesiredTemperature, setDesiredTemperature } from './requests';

function App() {
    const [desiredTemp, setDesiredTemp] = useState(200);
    const [temperatureData, setTemperatureData] = useState({});

    useEffect(() => {
        getDesiredTemperature().then((data) => {
            setDesiredTemp(data.desired_temp * 10);
        });
        getAllTemperatureData().then((data) => {
            setTemperatureData(data.pop());
        });

        let interval = setInterval(() => {
            getAllTemperatureData().then((data) => {
                setTemperatureData(data.pop());
            });
        }, 15000);

        return () => {
            clearInterval(interval);
        };
    }, []);

    const setDesiredTemperatureHandler = () => {
        setDesiredTemperature(Math.floor(desiredTemp / 10)).then((data) => {
            console.log(data);
        });
    };

    return (
        <AppContainer>
            <TemperatureInfo>Temperature inside: {temperatureData?.temp_in}°C, outside: {temperatureData?.temp_out}°C</TemperatureInfo>
            <div class="slidecontainer">
                <input type="range" min="100" max="400" value={desiredTemp} className="desired-temp"
                    onChange={(e) => setDesiredTemp(e.target.value)} />
                <div className="slidertext">{Math.floor(desiredTemp / 10)}.0°C</div>
            </div>
            <button onClick={() => setDesiredTemperatureHandler()}>Apply desired temperature</button>
        </AppContainer>
    );
}

export default App;