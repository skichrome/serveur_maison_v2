### Serveur IoT basé sur un esp8266

#### Présentation générale
Ce projet écoute les données envoyée via un transmetteur nrf24l01 et confirme la bonne réception des données à l'émetteur. Les données reçues sont envoyées à un serveur NodeRed qui se charge de temporiser l'envoi des données à intervalle régulier vers une base de données distante (Node red est utilisé pour limiter le nombre de lectures / écritures sur la BDD).
Il sert également de moyen de paramétrer les dispositifs connectés au travers des transmetteurs nrf24l01. Seront reliés à cet esp8266 des volets roulants ainsi qu'une lampe RGB Yeelight (avec le mode développeur activé).

#### Communication avec l'esp8266 depuis le Wifi
Tout ce qui peut être commandé à distance ce fait grâce au protocole MQTT, via la librairie [ArduinoMqttClient](https://github.com/arduino-libraries/ArduinoMqttClient).
Les données collectées par l'esp8266 sont également transmis via le protocole MQTT. 

#### Communication radio 2.4GHz
L'esp8266 reçoit des données en provenance au minimum du projet [client_jardin_v1](https://github.com/skichrome/client_jardin_v1) qui prend des mesures en extérieur et gère l'arrosage automatisé. Il envoie également les commandes de l'arrosage via les modules radio nrf24l01.
Comme les projets reliés sont sur batterie et doivent savoir si les données sont bien transmises, l'esp8266 doit répondre à tout message pour que le client puisse se remettre en veille.

#### Capteurs
Afin de gérer l'allumage automatique de la lampe Yeelight un capteur pyroélectrique `HC-SR501`. Le mode automatique peut être activé ou désactivé via MQTT.