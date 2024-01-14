const axios = require('axios');
const url = 'http://[ARDUINO_WEBSERVER_HERE]';
axios.get(url)
  .then(response => {
    const jsonData = response.data;
    const weatherStation = jsonData.WeatherStation[0];
    console.log('Location:', weatherStation.location);
    console.log('Temperature Celsius:', weatherStation['temperature celsius']);
    console.log('Temperature Fahrenheit:', weatherStation['temperature fahrenheit']);
  })
  .catch(error => {
    console.error('Errore during HTTP request:', error.message);
  });
