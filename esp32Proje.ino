#include <WiFi.h>

const char *ssid = "dunyanın en guvenli wifi ağı";   // AP ağ adı
const char *password = "123456789";         // AP şifresi

void setup() {
  Serial.begin(115200);

  WiFi.softAP(ssid, password);

  Serial.println("Wi-Fi Access Point başlatıldı");
  Serial.print("Access Point IP Adresi: ");
  Serial.println(WiFi.softAPIP());  // AP'nin IP adresi

  delay(5000);  // baglanti için 5 saniye bekletme(delay)
  Serial.println("Bağlanan cihazlar:");  // baglanan cihazların bilgilerini yazdirir
  bagliCihazBilgileri();
}

void loop() {
  delay(10000);  // 10 saniyede bir güncellenebilir
}

void bagliCihazBilgileri() {
  uint8_t numDevices = WiFi.softAPgetStationNum();   //baglanan cihaz sayisini alir ve yazdirir 
  // uint8_t  = unsigned 8-bit integer 0 ile 255 arasındaki sayilari tanimlamak için kullanılır.
  Serial.print("Bağlanan cihaz sayısı: ");
  Serial.println(numDevices);

  if (numDevices > 0) {
    for (int i = 0; i < numDevices; i++) {
      uint8_t mac[6];
      IPAddress ip = WiFi.softAPIP(); 
      ip[3] = i + 2; 
      
      WiFi.softAPmacAddress(mac);  // cihazın mac adresini al

      String macStr = formatMacAddress(mac);

      Serial.print("Cihaz IP: ");
      Serial.println(ip);
      Serial.print("Cihaz MAC: ");
      Serial.println(macStr);
    }
  } else {
    Serial.println("Hiçbir cihaz bağlanmamış.");
  }
}

String formatMacAddress(uint8_t *mac) {
  String macStr = "";
  for (int i = 0; i < 6; i++) {
    macStr += String(mac[i], HEX);
    if (i < 5) macStr += ":";
  }
  return macStr;
}
