# iot_project

Main motive of the project is to check the nutrients of soil using colour sensor and also watering the plants based on the moisture and temperature collected from the sensor. NPK (Nitrogen Phosphorus Potassium) can be determined on basis of colour of the leaves. Also temperature at surface of the leaves determine whether they are healthy or not. With help of WiFi module, the messages/ emails of alarms regarding the moisture and nutrient content of the soil will be sent to the farmer. It aims to find the appropriate nutrient and moisture content for a particular crop grown by the farmer and store the data in the cloud. This way we can collect the data of different kinds of crop for future reference and improvements.

Implemented by using NodeMCU and color sensor(TCS3200).
ThingSpeak platform was used to upload the data produced by the sensor (R, G and B values). Used MATLAB analysis feature to analyse the data thus sending notifications to the farmer. Also used the ThingHTTP feature that helps triggering IFTTT link created to send mails to the farmer.

