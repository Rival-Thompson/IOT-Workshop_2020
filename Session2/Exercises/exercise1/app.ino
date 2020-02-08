int count = 0;

void setup()
{
  Serial.begin(115200);

}

void loop()
{
  count++;
  if (count >= 10)
  {
    Serial.println("10 loops completed");
    count = 0;
  }else
  {
    Serial.println(count);
  }  
}