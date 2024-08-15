#!/bin/bash

PSQL="psql --username=freecodecamp --dbname=salon --tuples-only -c"

echo -e "\n~~~~~ MY SALON ~~~~~\n"
echo -e "Welcome to My Salon, how may I help you?\n"

MAIN_MENU (){
  if [[ $1 ]]
  then
    echo -e "$1"
  fi
  
  #display all services
  SERVICE_LIST=$($PSQL "SELECT service_id, name FROM services")
  echo "$SERVICE_LIST" | while read SERVICE_ID BAR NAME
  do
    echo "$SERVICE_ID) $NAME"
  done

  #get service from user
  read SERVICE_ID_SELECTED
  SELECTED_SERVICE=$($PSQL "SELECT name FROM services WHERE service_id = $SERVICE_ID_SELECTED")
  if [[ -z $SELECTED_SERVICE ]]
  then
    MAIN_MENU "\nI could not find that service. What would you like today?"
  
  else
    #get customer details
    echo -e "\nWhat's your phone number?"
    read CUSTOMER_PHONE
    CUSTOMER_NAME=$($PSQL "SELECT name FROM customers WHERE phone = '$CUSTOMER_PHONE'")

    #if new customer
    if [[ -z $CUSTOMER_NAME ]]
    then
      #add new customer entry
      echo -e "\nI don't have a record for that phone number, what's your name?"
      read CUSTOMER_NAME
      INSERT_RESULT=$($PSQL "INSERT INTO customers (name, phone) VALUES('$CUSTOMER_NAME', '$CUSTOMER_PHONE')")

      # echo "Added customer entry for $CUSTOMER_NAME ($CUSTOMER_PHONE)"
    fi
    CUSTOMER_ID=$($PSQL "SELECT customer_id FROM customers WHERE phone = '$CUSTOMER_PHONE'")

    #get service time
    echo -e "\nWhat time would you like your $(echo $SELECTED_SERVICE | sed -r 's/^ *| *$//g'), $(echo $CUSTOMER_NAME | sed -r 's/^ *| *$//g')?"
    read SERVICE_TIME
    APPOINTMENT_RESULT=$($PSQL "INSERT INTO appointments(time, customer_id, service_id) VALUES('$SERVICE_TIME', $CUSTOMER_ID, $SERVICE_ID_SELECTED)")
    
    
    echo -e "\nI have put you down for a $(echo $SELECTED_SERVICE | sed -r 's/^ *| *$//g') at $SERVICE_TIME, $(echo $CUSTOMER_NAME | sed -r 's/^ *| *$//g').\n"
  fi
}

MAIN_MENU