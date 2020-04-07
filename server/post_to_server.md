
```ino
#include <Ethernet.h>
#include <SPI.h>



IPAddress ethernet_ip(192, 168, 0, 177);
byte ethernet_mac      [] = {0x78, 0xAC, 0xC0, 0x43, 0x7B, 0xC1};
byte ethernet_dns      [] = {192, 168, 0, 1};
byte ethernet_gateway  [] = {192, 168, 0, 1};
byte ethernet_subnet   [] = {255, 255, 255, 0};

EthernetServer _tspWebServer(80);
EthernetClient _tspWebServer_client;

bool _trgt4   = 0;
bool _trgt4I  = 0;
bool _trgrt1  = 0;
bool _trgrt1I = 0;
bool _trgrt2  = 0;
bool _trgrt2I = 0;
bool _trgrt3  = 0;
bool _trgrt3I = 0;
bool _trgrt4  = 0;
bool _trgrt4I = 0;
bool _trgrt5  = 0;
bool _trgrt5I = 0;
bool _trgt1   = 0;
bool _trgt1I  = 0;
bool _WSP2_A1 = 0;
bool _WSP2_A2 = 0;
bool _WSP2_A3 = 0;
bool _WSP2_A4 = 0;
bool _trgt2   = 0;
bool _trgt2I  = 0;
bool _trgt3   = 0;
bool _trgt3I  = 0;

//****************************
// Setup & init
//****************************
void setup() {
    Ethernet.begin(ethernet_mac, ethernet_ip, ethernet_dns, ethernet_gateway, ethernet_subnet);
    delay(1000);
    
    _tspWebServer.begin();
     pinMode(6, OUTPUT);
     pinMode(7, OUTPUT);
     pinMode(8, OUTPUT);
     pinMode(9, OUTPUT);
}


//****************************
// Base cycle
//****************************
void loop(){

_tspWebServer_client = _tspWebServer.available();

if (_tspWebServer_client) {

     boolean _WSCLineIsBlank = true;
     String  _WSCReqest      = "";
     bool    _WSCIsFirsLine  = 1;
     bool    _WSCIsParse     = 0;
     int     _WSCPageNumber  = 0;
     
while (_tspWebServer_client.connected()){ 
  while( _tspWebServer_client.available()){
       char _tempWebServerChar = _tspWebServer_client.read();
       
       if(_WSCIsFirsLine) {
          _WSCReqest+= _tempWebServerChar;
        }
        
       if (_tempWebServerChar == '\n' && _WSCLineIsBlank) {
           _sendWebServerPage(_WSCPageNumber); 
           break;
       }

       if (_tempWebServerChar == '\n') {
           _WSCLineIsBlank = true; 
           _WSCIsFirsLine=0; 
       
       if (!_WSCIsParse){ 
            _WSCPageNumber=_parseWebServerReqest(_WSCReqest); 
            _WSCIsParse=1;} 
        } else if (_tempWebServerChar != '\r') { 
            _WSCLineIsBlank = false;
        }
      }
  }
}


if (_WSP2_A1) { 
   
   if (_trgrt1I) { 
       _trgrt1 = 0;
    } else {
       _trgrt1  = 1; 
       _trgrt1I = 1;
    } 
 
 } else {
      _trgrt1  = 0; 
      _trgrt1I = 0;
 };
       
bool _tmp1 = _trgrt1;

if (_tmp1) { 
   if (! _trgt1I) _trgt1 = ! _trgt1; 
}

_trgt1I = _tmp1;

if (_WSP2_A2) { 
    if (_trgrt3I) { 
        _trgrt3 = 0;
     } else {
       _trgrt3  = 1; 
       _trgrt3I = 1;} 
    } else {
       _trgrt3  = 0; 
       _trgrt3I = 0;
  };
   
 bool _tmp2 = _trgrt3;

   if (_tmp2) { 
        if (! _trgt2I) 
              _trgt2 = ! _trgt2; 
        }
        
        _trgt2I = _tmp2;
        
     if (0) { 
         if (_trgrt2I) { 
             _trgrt2 = 0;
          }else {
             _trgrt2  = 1; 
             _trgrt2I = 1;
          } 
    } else {
           _trgrt2  = 0; 
           _trgrt2I = 0;
    };
    
if (_WSP2_A3) { 
    if (_trgrt4I) { 
        _trgrt4 = 0;
} else {
   _trgrt4  = 1; 
   _trgrt4I = 1;} 
 } else {
   _trgrt4  = 0; 
   _trgrt4I = 0;
};

bool _tmp3 = _trgrt4;

if (_tmp3) { 
    if (! _trgt3I) _trgt3 = ! _trgt3; }
     _trgt3I = _tmp3;
     
      if (_WSP2_A4) { 
           if (_trgrt5I) {  
               _trgrt5 = 0;
           } else {
               _trgrt5 = 1; 
               _trgrt5I = 1;} 
      } else {
              _trgrt5 = 0; 
              _trgrt5I = 0;
      };
      
bool _tmp4 = _trgrt5;

if (_tmp4) { 
   if (! _trgt4I) _trgt4 = ! _trgt4; 
}
    
_trgt4I = _tmp4;

digitalWrite(6, !(_trgt1));
digitalWrite(7, !(_trgt2));
digitalWrite(8, !(_trgt3));
digitalWrite(9, !(_trgt4));
}



//****************************
// Client
//****************************
void _sendWebServerPage(int sendPageNumber){
      _tspWebServer_client.println("HTTP/1.1 200 OK");
      _tspWebServer_client.println("Connection: close");
      _tspWebServer_client.println();
      _tspWebServer_client.println("<!DOCTYPE HTML PUBLIC ""-//W3C//DTD HTML 4.01 Transitional//EN"">");
      _tspWebServer_client.println("<html><head>");
      _tspWebServer_client.println("<META content=""text/html; charset=utf-8"" http-equiv=""Content-Type"">");
      _tspWebServer_client.println("</head><body>");
      
      if (sendPageNumber ==1) {
          _sendWebServerPage1();
      }
      
      if (sendPageNumber ==2) {
          _sendWebServerPage2();
      }
      
        _tspWebServer_client.println("</body></html>");
         delay(1); 
        _tspWebServer_client.stop();
}

//****************************
// Server request
//****************************
int _parseWebServerReqest(String reqestAddres) {
     int index;
     int result=0;
     index=reqestAddres.indexOf("/");
     reqestAddres = _stringWithoutCharWithIndex(reqestAddres,0,(index));
     index=reqestAddres.indexOf(" ");
     reqestAddres = _stringWithoutCharWithIndex(reqestAddres,index,(reqestAddres.length()-index));
     
     if (reqestAddres==""){
         result= 1;
     }
     
     if (reqestAddres=="1"){
         _WSP2_A1=1; 
         result= 2;
     } else {
         _WSP2_A1=0;
     }
     
     if (reqestAddres=="2"){
         _WSP2_A2=1; 
         result= 2;
     } else {
         _WSP2_A2=0;
     }
     
     if (reqestAddres=="3"){
         _WSP2_A3=1; 
         result= 2;
      } else {
         _WSP2_A3=0;
      }
      
     if (reqestAddres=="4"){
         _WSP2_A4=1; 
         result= 2;
      } else {
         _WSP2_A4=0;
     }
      return result;
}


//****************************
// String Index
//****************************
String _stringWithoutCharWithIndex(String value, int index,int count){
     String result="";
      
     for (int i=0; i <= value.length(); i++){
           if  ((i<index) ||(i>(index+count))){
               result+=value.charAt(i);
            }
     }
     return result;
}


//****************************
// Start page
//****************************
void _sendWebServerPage1(void){
_tspWebServer_client.println("");
_tspWebServer_client.println("<table width=""100%"" height=""100%"" cellspacing=""0"" cellpadding=""0"" border=""0"" bgcolor=""FFFFFF"">");
_tspWebServer_client.println("<tr>");
_tspWebServer_client.println("<td>");
_tspWebServer_client.println("");
_tspWebServer_client.println("");
_tspWebServer_client.println("");
_tspWebServer_client.println("<table width=""1200px"" align=""center"" border=""1"" cellspacing=""0"" cellpadding=""20"">");
_tspWebServer_client.println("");
_tspWebServer_client.println("");
_tspWebServer_client.println("");
_tspWebServer_client.println("");
_tspWebServer_client.println("");
_tspWebServer_client.println("");
_tspWebServer_client.println("<tr>");
_tspWebServer_client.println("");
_tspWebServer_client.println("");
_tspWebServer_client.println("<td width=""60%"" valign=""top"">");
_tspWebServer_client.println("<p><font color=""000000"" size=""5"" face=""Open Sans"">Управление нагрузкой</font></p>");
_tspWebServer_client.println("");
_tspWebServer_client.println("");
_tspWebServer_client.println("");
_tspWebServer_client.println("<table width=""60%"" cellspacing=""0"" cellpadding=""20"">");
_tspWebServer_client.println("<tr>");
_tspWebServer_client.println("<td>");
_tspWebServer_client.println("");
_tspWebServer_client.println("");
_tspWebServer_client.println("<p><a href=""http://192.168.0.177/1""><button>Реле 1</button></a></p>");
_tspWebServer_client.println("");
_tspWebServer_client.println("");
_tspWebServer_client.println("</td>");
_tspWebServer_client.println("");
_tspWebServer_client.println("<td>");
_tspWebServer_client.println("");
_tspWebServer_client.println("");
_tspWebServer_client.println("<p><a href=""""http://192.168.0.177/2""><button>Реле 2</button></a></p>");
_tspWebServer_client.println("");
_tspWebServer_client.println("");
_tspWebServer_client.println("</td>");
_tspWebServer_client.println("");
_tspWebServer_client.println("<td>");
_tspWebServer_client.println("");
_tspWebServer_client.println("");
_tspWebServer_client.println("<p><a href=""""http://192.168.0.177/3""><button>Реле 3</button></a></p>");
_tspWebServer_client.println("");
_tspWebServer_client.println("");
_tspWebServer_client.println("</td>");
_tspWebServer_client.println("");
_tspWebServer_client.println("<td>");
_tspWebServer_client.println("");
_tspWebServer_client.println("");
_tspWebServer_client.println("<p><a href=""""http://192.168.0.177/4""><button>Реле 4</button></a></p>");
_tspWebServer_client.println("");
_tspWebServer_client.println("");
_tspWebServer_client.println("</td>");
_tspWebServer_client.println("");
_tspWebServer_client.println("</tr>");
_tspWebServer_client.println("</table>");
_tspWebServer_client.println("");
_tspWebServer_client.println("");
_tspWebServer_client.println("</td>");
_tspWebServer_client.println("");
_tspWebServer_client.println("");
_tspWebServer_client.println("");
_tspWebServer_client.println("");
_tspWebServer_client.println("");
_tspWebServer_client.println("");
_tspWebServer_client.println("</table>");
_tspWebServer_client.println("");
_tspWebServer_client.println("</td>");
_tspWebServer_client.println("</tr>");
_tspWebServer_client.println("</table>");
_tspWebServer_client.println("");
}

//****************************
// Page server
//****************************
void _sendWebServerPage2(void) {
     _tspWebServer_client.println("<meta http-equiv=""refresh"" content=""0;URL=http://192.168.0.177"">");
}
```
