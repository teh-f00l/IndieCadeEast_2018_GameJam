bool rebel = true;
byte death = 0;
byte trusting = 3;
byte cautious = 4;
byte currState = 5;
int trust = 0;

int utility=255;
//uint16_t y=rand(utility);
//serial number used to determine initial loyalty
byte x=getSerialNumberByte(1);
//allow for easy state changes
void setState(byte s)
{
  currState = s;
}


void setup() {
  // put your setup code here, to run once:
  //set status(loyalist or rebel)
  if(x % 2 ==0){
  rebel=false;
  setState(3);
  }
else{
  rebel=true;
  setState(4);
}
}

void switch_sides(){

  if (rebel==true){
    rebel=false;
  }
  if (rebel=false){
    rebel=true;
  }
}


void loop() {
  // put your main code here, to run repeatedly:
  if (buttonSingleClicked()){
    utility += 100;
  }

  if (buttonDoubleClicked()){
    utility -= 200;
      if (utility < 200){
    switch_sides();
  }  
  }
  if (buttonMultiClicked()){
    utility = 0;
    setColor(OFF); 
  }

// interact with neighbors

FOREACH_FACE(f) {
//do neighbors trust each other?
  if (getLastValueReceivedOnFace(f)== trust ){
    setFaceColor(f, GREEN);
    utility +=100;
  // switch trust value to correspond with team
    if (currState==3 && rebel==false){
      setState(4);
// if the other block has different trust status, the other block is an enemy and they betray eachother!
      if (getLastValueReceivedOnFace(f) !=currState){
      setFaceColor(f, RED);
      utility-=300;
      
    }
    }
    // confident in revealing patriotism
    if (utility>=500 && rebel==false){
      setFaceColor(f, BLUE);
    }
//confident in revealing rebelliousness
    if(utility>=500 && rebel == true){
      setFaceColor(f, WHITE);
    }
    
    }    
    // uncertain of neighbor's side and uncomfortable around them
  if (getLastValueReceivedOnFace(f) != currState){
    setFaceColor(f, RED);
    utility-=100;
    
  }
//check for death, if dead, remove from board
if (utility <=0) {
  setColor(OFF);
  setState(0);
}

  } 
  }
