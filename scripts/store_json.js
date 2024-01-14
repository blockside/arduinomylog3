const axios = require('axios');
const url = 'http://[ARDUINO_WEBSERVER_HERE]';
axios.get(url)
  .then(async response => {
    const jsonData = response.data;
    const weatherStation = jsonData.WeatherStation[0];
   if (weatherStation && 'temperature celsius' in weatherStation) {
   const temperatureCelsius = parseInt(parseFloat(weatherStation['temperature celsius']) * 100);
   await main(temperatureCelsius);
  }
  else {
  console.error('Dato non valido.');
  process.exit(1);
       }
    } 
  );
  async function main(temperatureCelsius) {
  console.log('Temperature retrieved from JSON:', temperatureCelsius);
  const address = '[YOUR_SMART_CONTRACT_ADDRESS_HERE]';
  const Box = await ethers.getContractFactory('Box');
  const box = await Box.attach(address);
  let tx;
  tx = await box.store(temperatureCelsius);
  await tx.wait();
  const value = await box.retrieve();
  console.log('Temperature stored into blockchain:', value.toString());
};
