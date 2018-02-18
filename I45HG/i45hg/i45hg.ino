//states
byte s_Begin = 1;
byte s_White = 2;
byte s_Black = 3;
byte s_checking = 4;
byte s_beenPressed = 5;
byte currState = 1;
byte unused = 0;
byte getSerialNumberByte( byte n );



void setState(byte s)
{
  currState = s;
}

void setup() {
  // put your setup code here, to run once:
  setColor(BLUE);
  setValueSentOnAllFaces(1);
  setState(1);

}

void loop() {
  // put your main code here, to run repeatedly:

  if(buttonSingleClicked() && currState != 5)
  {
    setColor(RED);
    setValueSentOnAllFaces(3);
    setState(4);
  }

  if(currState != 1)
  {
    setState(5);
    int tmp_black_neighbors = 0;
  
    FOREACH_FACE(f)
    {
      (getLastValueReceivedOnFace(f) == 3) ? tmp_black_neighbors++ : unused++;
    }
  
    if(tmp_black_neighbors > 2)
    {

      
      setValueSentOnAllFaces(0);
      setColor(OFF);
      setState(0);
    }
  }
}
