#!/bin/bash

#check argument
if [[ ! $1 ]]
then
  echo "Please provide an element as an argument."
else
  PSQL="psql --username=freecodecamp --dbname=periodic_table --tuples-only -c"

  #get element data
  if [[ $1 =~ ^[0-9]+$ ]]
  then
    RESULTS=$($PSQL "SELECT atomic_number, symbol, name, atomic_mass, melting_point_celsius, boiling_point_celsius, type FROM elements LEFT JOIN properties USING(atomic_number) LEFT JOIN types USING(type_id) WHERE elements.atomic_number=$1")
  else
    RESULTS=$($PSQL "SELECT atomic_number, symbol, name, atomic_mass, melting_point_celsius, boiling_point_celsius, type FROM elements LEFT JOIN properties USING(atomic_number) LEFT JOIN types USING(type_id) WHERE elements.name='$1' OR elements.symbol='$1'")
  fi
  
  #not found
  if [[ -z $RESULTS ]]
  then
    echo "I could not find that element in the database."
  
  else
    #display data
    echo "$RESULTS" | while read ATOMIC_NUMBER BAR SYMBOL BAR NAME BAR ATOMIC_MASS BAR MELTING BAR BOILING BAR TYPE
    do
      echo "The element with atomic number $ATOMIC_NUMBER is $NAME ($SYMBOL). It's a $TYPE, with a mass of $ATOMIC_MASS amu. $NAME has a melting point of $MELTING celsius and a boiling point of $BOILING celsius."
    done
  fi

fi