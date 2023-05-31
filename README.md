## Código Python

O código Python é uma aplicação Flask que utiliza a biblioteca Flask para criar um servidor web. Ele recebe solicitações GET e retorna informações sobre o saldo de uma conta bancária. Abaixo estão as explicações dos principais pontos do código:

1. Importação de bibliotecas:
   - `from flask import Flask, request`: Importa a classe Flask e o objeto request da biblioteca Flask. Essas bibliotecas são usadas para criar o servidor web e processar as solicitações HTTP.

2. Definição das variáveis:
   - `app = Flask(__name__)`: Cria uma instância da classe Flask para iniciar o servidor.
   - `url_banco = "https://www.asaas.com/api/v3/finance/balance"`: Define a URL da API que será utilizada para obter o saldo bancário.
   - `headers`: Define os cabeçalhos da solicitação HTTP, incluindo o token de acesso necessário para autenticação.
   - `prev = [2]`: Cria uma lista para armazenar os saldos anteriores.

3. Rota e função principal:
   - `@app.route("/", methods=['POST', 'GET'])`: Define a rota principal do servidor. Aceita solicitações GET e POST.
   - `def enviar()`: Função que será executada quando uma solicitação for feita para a rota principal.
   - `if request.method == "GET":`: Verifica se a solicitação é do tipo GET.
   - `response = requests.get(url_banco, headers=headers)`: Faz uma solicitação GET para a URL da API para obter o saldo bancário.
   - `real = json.loads(response.text)`: Converte a resposta em um objeto JSON.
   - `js = real['balance']`: Obtém o saldo da conta bancária a partir do objeto JSON.
   - `if js not in prev:`: Verifica se o saldo atual não está presente na lista de saldos anteriores.
   - `diferenca = float(js) - float(prev[-1])`: Calcula a diferença entre o saldo atual e o saldo anterior.
   - `text = f'R${diferenca:.2f} recebido!'`: Formata uma string com a diferença de saldo.
   - `prev.append(js)`: Adiciona o saldo atual à lista de saldos anteriores.
   - `return text`: Retorna a diferença de saldo se for a primeira vez que o saldo é recebido, caso contrário, retorna o saldo atual.

4. Execução do servidor:
   - `if __name__ == "__main__":`: Verifica se o código está sendo executado diretamente (não importado como módulo).
   - `serve(app, host="0.0.0.0", port=8080)`: Inicia o servidor Flask usando o Waitress como servidor HTTP.

## Código Arduino

O código Arduino utiliza um microcontrolador ESP8266 para se conectar a uma rede Wi-Fi e fazer uma solicitação HTTPS a uma API. Abaixo estão as explicações dos principais pontos do código:

1. Importação de bibliotecas:
   - `#include <LiquidCrystal_I2C.h>`: Importa a biblioteca LiquidCrystal_I2C, que é utilizada para controlar um display LCD de 16x2 através de uma conexão I2C.
   - `#include <ESP8266WiFi.h>`: Importa a biblioteca ESP8266WiFi, que é responsável por gerenciar a conexão Wi-Fi do ESP8266.
   - `#include <ESP8266HTTPClient.h>`: Importa a biblioteca ESP8266HTTPClient, que fornece uma interface simplificada para fazer solicitações HTTP.
   - `#include <WiFiClientSecureBearSSL.h>`: Importa a biblioteca WiFiClientSecureBearSSL, que permite criar uma conexão segura SSL/TLS.

2. Definição das variáveis:
   - `const char* ssid = "wifi_name";`: Define o nome da rede Wi-Fi à qual o ESP8266 irá se conectar. Substitua "wifi_name" pelo nome correto da sua rede.
   - `const char* password = "wifi_password";`: Define a senha da rede Wi-Fi. Substitua "wifi_password" pela senha correta da sua rede.
   - `const int lcdColumns = 16;`: Define o número de colunas do display LCD.
   - `const int lcdRows = 2;`: Define o número de linhas do display LCD.
   - `LiquidCrystal_I2C lcd(0x3F, lcdColumns, lcdRows);`: Cria uma instância da classe LiquidCrystal_I2C para controlar o display LCD.

3. Configuração inicial:
   - `void setup()`: Função executada uma vez no início do programa.
   - `pinMode(buttonPin, INPUT);`: Configura o pino do botão como entrada.
   - `lcd.init();`: Inicializa o display LCD.
   - `lcd.backlight();`: Liga o backlight do display LCD.
   - `WiFi.mode(WIFI_STA);`: Configura o modo de operação do ESP8266 para estação (cliente) Wi-Fi.
   - `WiFi.begin(ssid, password);`: Inicia a conexão com a rede Wi-Fi utilizando o nome e senha definidos anteriormente.
   - `lcd.print("Procurando WI-FI");`: Exibe a mensagem "Procurando WI-FI" no display LCD.
   - `while (WiFi.waitForConnectResult() != WL_CONNECTED) { delay(1000); }`: Aguarda a conexão Wi-Fi ser estabelecida. A função `WiFi.waitForConnectResult()` retorna quando a conexão é bem-sucedida (retorna `WL_CONNECTED`) ou ocorre algum erro.

4. Loop principal:
   - `void loop()`: Função executada continuamente após a configuração inicial.
   - `int buttonState = digitalRead(buttonPin);`: Lê o estado do botão.
   - `if (WiFi.status() == WL_CONNECTED) {`: Verifica se o ESP8266 está conectado à rede Wi-Fi.
   - `std::unique_ptr<BearSSL::WiFiClientSecure> client(new BearSSL::WiFiClientSecure);`: Cria um objeto client do tipo WiFiClientSecureBearSSL para estabelecer uma conexão segura com o servidor.
   - `client->setInsecure();`: Desativa a verificação de certificado SSL, permitindo conexões com servidores sem certificado válido.
   - `HTTPClient https;`: Cria um objeto https do tipo HTTPClient para fazer a solicitação HTTP.
   - `if (https.begin(*client, "your_api")) {`: Inicia a solicitação HTTP para a URL da API desejada. Substitua "your_api" pelo endereço correto da API.
   - `int httpCode = https.GET();`: Realiza uma solicitação GET e armazena o código de status HTTP retornado.
   - `if (httpCode > 0) {`: Verifica se a solicitação foi bem-sucedida (código de status HTTP maior que zero).
   - `if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {`: Verifica se o código de status HTTP é OK (200) ou MOVED_PERMANENTLY (301).
   - `String payload = https.getString();`: Obtém a resposta da solicitação HTTP como uma string.
   - `lcd.clear();`: Limpa o display LCD.
   - `Serial.println(payload);`: Imprime a resposta no monitor serial.
   - `lcd.setCursor(0, 0);`: Define a posição do cursor do display LCD.
   - `lcd.print(payload);`: Exibe a resposta no display LCD.
   - `https.end();`: Encerra a conexão HTTP.
   - `} else {`: Caso não seja possível estabelecer a conexão com o servidor.
   - `Serial.printf("[HTTPS] Unable to connect\n");`: Exibe uma mensagem de erro no monitor serial.
   - `}`: Fecha o bloco `if (https.begin(*client, "your_api"))`.
   - `}`: Fecha o bloco `if (WiFi.status() == WL_CONNECTED)`.

5. Delay:
   - `delay(1000);`: Aguarda 1 segundo antes de repetir o loop principal.
