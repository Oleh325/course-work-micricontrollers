import styled from "styled-components";

export const AppContainer = styled.div`
    display: flex;
    align-items: center;
    justify-content: center;
    flex-direction: column;
    height: 100vh;
    gap: 2rem;

    button {
        background-color: #737373;
        border: none;
        border-radius: 0.7rem;
        font-size: 1.5rem;
        padding: 0.5rem 1rem;
        cursor: pointer;
        margin-bottom: 3rem;
    }
    button:hover {
        background-color: #4F4F4F;
    }
    button:active {
        background-color: #2B2B2B;
    }
    .desired-temp {

    }
    .slidecontainer {
        display: flex;
        justify-content: space-between;
        align-items: center;
        width: 35%;
        input {
            width: 90%;
        }
        .slidertext {
            font-weight: 600;
            font-size: 1.2rem;
        }
    }
`;

export const TemperatureInfo = styled.div`
    font-size: 2.5rem;
    font-weight: 600;
    margin-bottom: 3rem;
`;
