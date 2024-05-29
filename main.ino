#define ComunicacaoUART Serial

void setup() {
  Serial.begin(115200);
  ComunicacaoUART.begin(115200);
  conectaWifi();
}

void loop() {
  verificarEstadoDispositivos("luz-cantina");
  verificarEstadoDispositivos("luz-andar00-sala01");
  verificarEstadoDispositivos("luz-andar00-sala02");
  verificarEstadoDispositivos("luz-banheiro-masculino");
  verificarEstadoDispositivos("luz-banheiro-feminino");
  verificarEstadoDispositivos("luz-hall");
  verificarEstadoDispositivos("luz-apartamento");
  verificarEstadoDispositivos("luz-andar01-sala01");
  verificarEstadoDispositivos("luz-area-circulacao");
  verificarEstadoDispositivos("luz-cozinha");
  verificarEstadoDispositivos("luz-area-servico");
  verificarEstadoDispositivos("luz-suite");
  verificarEstadoDispositivos("luz-banheiro-suite");
  verificarEstadoDispositivos("luz-banheiro-social");
  verificarEstadoDispositivos("luz-estufa");
  recebeDadosArduino();
}
