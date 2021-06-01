
//https://core.ac.uk/download/pdf/234019731.pdf

#define anInput 33 // pin analogo del  MQ135
#define co2Zero 55 //calibracion CO2 nivel 0
//#define led     9

//SETUP

void setup() {
pinMode(anInput,INPUT); 
pinMode(led,OUTPUT);
Serial.begin(9600);  
}

//LOOP
void loop()
{
int co2now[10]; // guarda 10 valores medidos de CO2
int co2prom = 0; // promedio de los datos medidos
int co2comp = 0; //valor real despues de la compensación
int co2ppm = 0; // dato del gráfico
int suma = 0;
int FR=0;
int FR[65];
int i=0;
int tiempo =0;
int actu=15000;// despues de 15 segundos lee
int valorreal=0;
int j=0;
int CO[65];


//------------------------------------------------------------------------------------
//Obtención de ls frecuencia respiratoria

//Contar el tiempo
tiempo =millis();


//Los primeros 15 segundos de toma de muestra
while (t<=14000){

//Entrega el valor de la CO2 trabajada
for (int x = 0;x<10;x++){ // guardar los valores medidos
co2now[x]=analogRead(A0); 
delay(200); //se le da un rango algo para que el gas analizado queda dentro de la cavidad durante un tiempo, aunque no se continue administrando mas del gas
}

for (int x = 0;x<10;x++){ // agregamos las muestras
suma=suma + co2now[x];
}

co2prom = suma/10;  //tenemos el promedio
co2comp = co2prom - co2Zero; // tenemos la compensación
//proporcional al voltaje
co2ppm = map(co2comp,0,4095,400,5000); // mapeo el valor de la lectura a los niveles de la atmosfera

for (int x = 0;x<60;x++){
CO[x]=co2ppm;
}

for (int i = 0;i<60;i++){
//Las variaciones de Co2 (comprobar)
if  (CO[i+1]-30>CO[i]){ // Si el valor de la atmosfera aumenta en 30 aprox es una inhalacion (aprox)
FR[j]=1;
j=j+1;
}else{
FR[j]=0;
j=j+1;	
}
}
//Resolución 12 bits



}// Primeros 14 segundos....
//------------------

//_______ Rebovación de segundo
//Entrega el valor de la CO2 trabajada
for (int x = 0;x<10;x++){ // guardar los valores medidos
co2now[x]=analogRead(A0); 
delay(200); //se le da un rango algo para que el gas analizado queda dentro de la cavidad durante un tiempo, aunque no se continue administrando mas del gas
}

for (int x = 0;x<10;x++){ // agregamos las muestras
suma=suma + co2now[x];
}

co2prom = suma/10;  //tenemos el promedio
co2comp = co2prom - co2Zero; // tenemos la compensación
//proporcional al voltaje
co2ppm = map(co2comp,0,4095,400,5000); // mapeo el valor de la lectura a los niveles de la atmosfera

for (int x = 56;x<60;x++){
CO[x]=co2ppm;
}


//Me ve el último segundo
for (int i = 60;i<64;i++){
//Las variaciones de Co2 (comprobar)
if  (CO[i+1]-30>CO[i]){ // Si el valor de la atmosfera aumenta en 30 aprox es una inhalacion (aprox)
FR[j]=1;
j=j+1;
}else{
FR[j]=0;
j=j+1;	
}
}

//Eliminando del arreglo por segundo
if (actu=tiempo){
	i=1;
    CO[0]=CO[3];
	actu=actu+1000;

/// sumando los valores picos para mostrar la impresión
for (int m = 0;m<60;m++){ 
FR=FR+FR[m]
}
valorreal=4*FR; // muestra los últimos 15 segundps*4
Serial.println(valorreal);
}//if

//Actualización de los datos
for (int z= 4;z<56;z++){ 
FR[z-4]=FR[z];/
}

j=60// Teemplazar las últimas 5 muestras

}//loop



//int *CO2 (int valorCO2[], int size){
//	return CO2;
//}
