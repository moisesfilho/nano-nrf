#include <Arduino.h>
#include <Servo.h>

int suavidade = 20;

Servo eixo;

int eixoPin = A0;
int eixoEsquerda = 10;
int eixoCentro = 97;
int eixoDireita = 180;
int eixoPosition = eixoCentro;

Servo vertical;

int verticalPin = A1;
int verticalMinimo = 10;
int verticalMaximo = 60;
int verticalPosition = verticalMinimo;

Servo frenteAtras;

int frenteAtrasPin = A2;
int frenteAtrasMinimo = 0;
int frenteAtrasMaximo = 100;
int frenteAtrasPosition = frenteAtrasMinimo;

Servo garra;

int garraPin = A3;
int garraFechada = 95;
int garraAberta = 5;
boolean garraEstado = false;

void attachServos()
{
  eixo.attach(eixoPin);
  vertical.attach(verticalPin);
  frenteAtras.attach(frenteAtrasPin);
  garra.attach(garraPin);
}

void testeEixo()
{
  eixo.write(eixoEsquerda);
  delay(1000);
  eixo.write(eixoCentro);
  delay(1000);
  eixo.write(eixoDireita);
  delay(1000);
  eixo.write(eixoCentro);
  delay(1000);
}

void testeVertical()
{
  for (int i = verticalMinimo; i < verticalMaximo; i++)
  {
    vertical.write(i);
    delay(suavidade);
  }

  for (int i = verticalMaximo; i >= verticalMinimo; i--)
  {
    vertical.write(i);
    delay(suavidade);
  }
}

void testeFrenteTras()
{
  for (int i = frenteAtrasMinimo; i < frenteAtrasMaximo; i = i + 2)
  {
    frenteAtras.write(i);
    delay(suavidade * 2);
  }

  for (int i = frenteAtrasMaximo; i >= frenteAtrasMinimo; i = i - 2)
  {
    frenteAtras.write(i);
    delay(suavidade * 2);
  }
}

void testeGarra()
{
  for (int i = garraFechada; i >= garraAberta; i--)
  {
    garra.write(i);
    delay(suavidade);
  }

  for (int i = garraAberta; i < garraFechada; i++)
  {
    garra.write(i);
    delay(suavidade);
  }
}

void thau()
{
  vertical.write(verticalMinimo);
  for (int i = verticalMinimo; i < verticalMaximo; i++)
  {
    vertical.write(i);
    delay(suavidade);
  }

  eixo.write(eixoEsquerda + 50);
  delay(300);
  eixo.write(eixoDireita - 50);
  delay(300);
  eixo.write(eixoEsquerda + 50);
  delay(300);
  eixo.write(eixoDireita - 50);
  delay(300);
  eixo.write(eixoCentro);
  delay(1000);

  vertical.write(verticalMinimo);
}

void testes()
{
  testeEixo();
  testeVertical();
  testeFrenteTras();
  testeGarra();
}

void posicaoInicial()
{
  eixo.write(eixoCentro);
  vertical.write(verticalMinimo);
  frenteAtras.write(frenteAtrasMinimo);
  garra.write(garraFechada);
}

void up()
{
  if (verticalPosition < verticalMaximo)
  {
    verticalPosition++;
    vertical.write(verticalPosition);
    delay(suavidade);
  }
}

void down()
{
  if (verticalPosition > verticalMinimo)
  {
    verticalPosition--;
    vertical.write(verticalPosition);
    delay(suavidade);
  }
}

void left()
{
  if (eixoPosition > eixoEsquerda)
  {
    eixoPosition--;
    eixo.write(eixoPosition);
    delay(suavidade + 30);
  }
}

void right()
{
  if (eixoPosition < eixoDireita)
  {
    eixoPosition++;
    eixo.write(eixoPosition);
    delay(suavidade + 30);
  }
}

void forward()
{
  if (frenteAtrasPosition < frenteAtrasMaximo)
  {
    frenteAtrasPosition++;
    frenteAtras.write(frenteAtrasPosition);
    delay(suavidade);
  }
}

void backward()
{
  if (frenteAtrasPosition > frenteAtrasMinimo)
  {
    frenteAtrasPosition--;
    frenteAtras.write(frenteAtrasPosition);
    delay(suavidade);
  }
}

void open()
{
  for (int i = garraFechada; i >= garraAberta; i--)
  {
    garra.write(i);
    delay(suavidade);
  }
}

void close()
{
  for (int i = garraAberta; i < garraFechada; i++)
  {
    garra.write(i);
    delay(suavidade);
  }
}

void setupBraco()
{
  attachServos();
  posicaoInicial();
}

int lastSwitchState = LOW;

void loopBraco()
{
  if (!BUTTON_A)
  {
    up();
  }

  if (!BUTTON_C)
  {
    down();
  }

  if (!BUTTON_D)
  {
    left();
  }

  if (!BUTTON_B)
  {
    right();
  }

  if (!BUTTON_F)
  {
    forward();
  }

  if (!BUTTON_E)
  {
    backward();
  }

  if (!BUTTON_G)
  {
    if (garraEstado == false)
    {
      garraEstado = true;
      close();
    }        
    else
    {
      garraEstado = false;
      open();
    }
  }
}