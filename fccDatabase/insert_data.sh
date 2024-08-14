#! /bin/bash
# Script to insert data from games.csv worldcup database

if [[ $1 == "test" ]]
then
  PSQL="psql --username=postgres --dbname=worldcuptest -t --no-align -c"
else
  PSQL="psql --username=freecodecamp --dbname=worldcup -t --no-align -c"
fi

# Do not change code above this line. Use the PSQL variable above to query your database.

echo "$($PSQL "TRUNCATE games, teams")"

cat games.csv | while IFS=',' read YEAR ROUND TEAM1 TEAM2 GOAL1 GOAL2
do
  if [[ $YEAR != "year" ]]
  then
    #get team_id 1
    TEAM1_ID=$($PSQL "SELECT team_id FROM teams WHERE name='$TEAM1'")
    #if not present
    if [[ -z $TEAM1_ID ]]
    then
      #insert team
      INSERT_TEAM_RESULT=$($PSQL "INSERT INTO teams(name) VALUES('$TEAM1')")
      if [[ $INSERT_TEAM_RESULT == "INSERT 0 1" ]]
      then
        echo "Inserted into teams, $TEAM1"
      fi
      TEAM1_ID=$($PSQL "SELECT team_id FROM teams WHERE name='$TEAM1'")
    fi

    #get team_id 2
    TEAM2_ID=$($PSQL "SELECT team_id FROM teams WHERE name='$TEAM2'")
    #if not present
    if [[ -z $TEAM2_ID ]]
    then
      #insert team
      INSERT_TEAM_RESULT=$($PSQL "INSERT INTO teams(name) VALUES('$TEAM2')")
      if [[ $INSERT_TEAM_RESULT == "INSERT 0 1" ]]
      then
        echo "Inserted into teams, $TEAM2"
      fi
      TEAM2_ID=$($PSQL "SELECT team_id FROM teams WHERE name='$TEAM2'")
    fi

    #insert match data
    if [[ $GOAL1 > $GOAL2 ]]
    then
      GAME_INSERT_RESULT=$($PSQL "INSERT INTO games(year, round, winner_id, opponent_id, winner_goals, opponent_goals) VALUES('$YEAR', '$ROUND', $TEAM1_ID, $TEAM2_ID, $GOAL1, $GOAL2)")
      if [[ $GAME_INSERT_RESULT == "INSERT 0 1" ]]
      then
        echo "Inserted into games, $YEAR $ROUND"
      fi
    else
      GAME_INSERT_RESULT=$($PSQL "INSERT INTO games(year, round, winner_id, opponent_id, winner_goals, opponent_goals) VALUES('$YEAR', '$ROUND', $TEAM2_ID, $TEAM1_ID, $GOAL2, $GOAL1)")
      if [[ $GAME_INSERT_RESULT == "INSERT 0 1" ]]
      then
        echo "Inserted into games, $YEAR $ROUND"
      fi
    fi

  fi
done