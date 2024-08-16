#!/bin/bash
#game to guess a secret number based on hints given

#connect to database
PSQL="psql --username=freecodecamp --dbname=number_guess --no-align --tuples-only -c"
echo -e "\n~~~~~ NUMBER GUESSING GAME ~~~~~\n"

#login user
echo "Enter your username:"
read USERNAME

USER_DATA=$($PSQL "SELECT games_played, best_game FROM players WHERE username='$USERNAME'")

#if new user
if [[ -z $USER_DATA ]]
then
  echo "Welcome, $USERNAME! It looks like this is your first time here."
  INSERT_RESULT=$($PSQL "INSERT INTO players(username) VALUES('$USERNAME')")

#existing user
else
  ORIGINAL_IFS=$IFS
  IFS="|"
  read -r GAMES_PLAYED BEST_GAME <<< "$USER_DATA"
  echo "Welcome back, $USERNAME! You have played $GAMES_PLAYED games, and your best game took $BEST_GAME guesses."
  IFS=$ORIGINAL_IFS
fi


#set up variables
GUESS=0
GUESSES=0
SECRET_NUMBER=$(( $RANDOM % 1000 + 1 ))

echo -e "\nGuess the secret number between 1 and 1000:\n"

#read player guess
while [[ $GUESS != $SECRET_NUMBER ]]
do
  read GUESS
  GUESSES=$(( $GUESSES+1 ))
  
  if [[ ! $GUESS =~ ^[0-9]+$ ]]; then
    echo -e "That is not an integer, guess again:\n"
  elif [[ $GUESS -gt $SECRET_NUMBER ]]; then
    echo -e "It's lower than that, guess again:\n"
  elif [[ $GUESS -lt $SECRET_NUMBER ]]; then
    echo -e "It's higher than that, guess again:\n"
  fi
done

echo -e "\nYou guessed it in $GUESSES tries. The secret number was $SECRET_NUMBER. Nice job!"

#update database
GAMES_PLAYED=$(( $GAMES_PLAYED+1 ))

#new player
if [[ -z $USER_DATA ]]
then
  UPDATE_DATA=$($PSQL "UPDATE players SET games_played=$GAMES_PLAYED, best_game=$GUESSES WHERE username='$USERNAME'")

#existing player
else
  if [[ $GUESSES -lt $BEST_GAME ]]; then
    UPDATE_DATA=$($PSQL "UPDATE players SET games_played=$GAMES_PLAYED, best_game=$GUESSES WHERE username='$USERNAME'")
  else
    UPDATE_DATA=$($PSQL "UPDATE players SET games_played=$GAMES_PLAYED WHERE username='$USERNAME'")
  fi
  
fi
