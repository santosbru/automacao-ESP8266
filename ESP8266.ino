#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

#define BOTtoken "952404129:AAGaQAYz53Q1jCy_xaWDyTjk3OY9sSiqWkY"//Define o Token do BOT (@Rbonsaibot)
 
WiFiClientSecure client;    //Cria um cliente seguro (para ter acesso ao HTTPS)
UniversalTelegramBot bot(BOTtoken, client);
 
String id, text;      //Váriaveis para armazenamento do ID e TEXTO gerado pelo Usuario
unsigned long tempo;

String key = "?key=AIzaSyCdL36YuZP0zSLVvfwTzj4eyoj5cpJDBfE"; //(api key)

//https://docs.google.com/spreadsheets/d/1utN1nvpqmOg8RhKBAvAiMiKajJ80Wxx9lxMJGXixjco/edit?usp=sharing (Link da Planilha)


void setup(void)
{
   pinMode(13, OUTPUT);//LED conectado à saida  
   pinMode(14, OUTPUT);
   WiFi.mode(WIFI_STA);//Define o WiFi como Estaçao
   connect();//Funçao para Conectar ao WiFi
   
   Serial.println("");
   Serial.print("Connected to ");
   Serial.print("IP address: ");
   Serial.println(WiFi.localIP());
   
}


void connect()//Funçao para Conectar ao wifi e verificar à conexao.
{
   if (WiFi.status() != WL_CONNECTED)//Caso nao esteja conectado ao WiFi, Ira conectarse
   {
      WiFi.begin("TP-Link", "oliv@123");//Insira suas informaçoes da rede
      Serial.print("WiFi.begin(Tp-link, oliv@123);");
      delay(1000);
   }
}


 
void loop()
{
   Serial.print("void loop");
   if (millis() - tempo > 2000)//Faz a verificaçao das funçoes a cada 2 Segundos
   {
      connect();//Funçao para verificar se ainda há conexao
      readTel();//Funçao para ler o telegram
      
      //delay(2000);
      tempo = millis();//Reseta o tempo
    }
}
 

 
void readTel()//Funçao que faz a leitura do Telegram.
{
   int newmsg = bot.getUpdates(bot.last_message_received + 1);
 
   for (int i = 0; i < newmsg; i++)//Caso haja X mensagens novas, fara este loop X Vezes.
   {
      id = bot.messages[i].chat_id;//Armazenara o ID do Usuario à Váriavel.
      text = bot.messages[i].text;//Armazenara o TEXTO do Usuario à Váriavel.
      text.toUpperCase();//Converte a STRING_TEXT inteiramente em Maiuscúla.
      
 
      if (text.indexOf("GARAGEM") > -1)//Caso o texto recebido contenha "GARAGEM"
      {
         digitalWrite(13, HIGH);//Liga o LED
         bot.sendMessage(id, "Portao Garagem Acionado", "");//Envia uma Mensagem para a pessoa que enviou o Comando.
         delay(1500);
         digitalWrite(13,LOW);
      }






      
 
      else if (text.indexOf("SOCIAL") > -1)//Caso o texto recebido contenha "SOCIAL"
      {
         digitalWrite(14, HIGH);//Liga o LED
         bot.sendMessage(id, "Portao Social Acionado"+id, "");//Envia uma Mensagem para a pessoa que enviou o Comando.
         Serial.println (id);
         delay(1500);
         digitalWrite(14,LOW);
      }



      
 
      else if (text.indexOf("/START") > -1)//Caso o texto recebido contenha "START"
      {
         //char boasvindas[] = ""
          bot.sendSimpleMessage(id,"Bem vindo ao Sistema de Automação Residencial Bonsai " ,"" );//Envia uma mensagem com seu ID.
          
      }
 
      else//Caso o texto recebido nao for nenhum dos acima, Envia uma mensagem de erro.
      {
         bot.sendSimpleMessage(id, "Comando Invalido", "");
      }
   }
 
}
