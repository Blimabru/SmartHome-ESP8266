#define ComunicacaoUART Serial

void setup() {
  Serial.begin(115200);
  ComunicacaoUART.begin(115200);
  conectaWifi();
}

void loop() {
  recebeDadosArduino();
  verificarEstadoDispositivo("luz-andar00-sala01");
  verificarEstadoDispositivo("luz-andar00-sala02");
}
