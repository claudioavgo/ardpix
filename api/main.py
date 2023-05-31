from flask import Flask, request
import requests
import json

app = Flask(__name__)

# URL da API para obter o saldo bancário
url_banco = "https://www.asaas.com/api/v3/finance/balance"

# Cabeçalhos da solicitação HTTP
headers = {
    "Content-Type": "application/json",
    "access_token": "COLOQUE SEU TOKEN AQUI!" # Mude esta linha para o token da sua API
}

# Lista para armazenar saldos anteriores
saldos_anteriores = [2]

@app.route("/", methods=['POST', 'GET'])
def enviar():
    if request.method == "GET":
        # Realiza uma solicitação GET para obter o saldo bancário
        resposta = requests.get(url_banco, headers=headers)
        dados = json.loads(resposta.text)
        saldo_atual = dados['balance']
        
        if saldo_atual not in saldos_anteriores:
            # Calcula a diferença entre o saldo atual e o saldo anterior
            diferenca = float(saldo_atual) - float(saldos_anteriores[-1])
            texto = f'R${diferenca:.2f} recebido!'
            saldos_anteriores.append(saldo_atual)
            return texto
        return f'Ganhos: R${saldo_atual}'

if __name__ == "__main__":
    from waitress import serve
    serve(app, host="0.0.0.0", port=8080)
