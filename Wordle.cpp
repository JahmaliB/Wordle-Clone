#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <ctime>
#include <cwchar>
#include <windows.h>
using namespace std;

#define MOVEUP "\033["
#define ERASELINE "\033[2K"

const string RED("\033[0;31m");
const string GREEN("\033[1;32m");
const string YELLOW("\033[1;33m");
const string BOLDWHITE ("\033[1m\033[37m");
const string BOLDRED ("\033[1m\033[31m");
const string DIMWHITE ("\033[2m\033[37m");
const string RESET("\033[0m");

const int MAX_LENGTH = 5;

void startScene();
string chooseRandom(vector<string> vec);
void input();
string checkWord(const string& guess, const string& answer, int MAX_LENGTH);
void endingScene(string guess, string answer, int numGuesses);
vector<string> readGuesses (int length);
vector<string> readSolutions (int length);

int main() 
{
  startScene();
  input();
  
  string x;
  cout << "Press 0 to exit program: ";
  cin >> x;
  return 0; 
}

void startScene()
{
  cout << BOLDWHITE;
  cout << "Welcome to Wordle!" << endl;
  cout << "Play by guessing 5-letter words." << endl;
  cout << "The feedback will give you clues:" << endl;
  cout << " RED    = Character not in word at all" << endl;
  cout << " GREEN  = Character found and position correct" << endl;
  cout << " YELLOW = Character found but position incorrect" << endl;
  cout << RESET;
  cout << "\n";
}

string chooseRandom(vector<string> vec) 
{
  auto iterator = vec.begin();
  int random_number = rand() % vec.size();
  advance(iterator, random_number);
  return iterator[0];
}

void input() 
{
  srand(time(0));
  bool flag = false;
  int numGuesses = 0;
  string guess;
  vector<string> all_solutions = readSolutions(MAX_LENGTH);
  vector<string> all_guesses = readGuesses(MAX_LENGTH);
  auto const answer = chooseRandom(all_solutions);

  do {
      cout << BOLDWHITE << "Guess a word (" + to_string(numGuesses + 1) + "/6): " << RESET; 
      cin >> guess;

      while (guess.length() != MAX_LENGTH) 
      {
        cout << string(MOVEUP) + "1F";
        cout << ERASELINE;
        cout << "Enter a 5 letter word: ";
        cin >> guess;
      }
      
      transform(guess.begin(), guess.end(), guess.begin(), ::toupper);

      if (find(all_guesses.begin(), all_guesses.end(), guess) != all_guesses.end()) 
      {
        string feedback = checkWord(guess, answer, MAX_LENGTH);
        string GuessText = "Guess a word (" + to_string(numGuesses + 1) + "/6): ";

        cout << string(MOVEUP) + "1F";
        cout << ERASELINE;
        cout << GuessText << feedback <<endl;
        numGuesses++;
      
      } 
      else 
      {
        cout << string(MOVEUP) + "1F";
        cout << ERASELINE;

        cout << "Guess a word (" + to_string(numGuesses + 1) + "/6): " << BOLDRED << "INVALID";
        cout << string(MOVEUP) + "1E";
      }

      if (guess == answer) 
      {
        flag = true;
      }

  } while (flag == false && numGuesses < 6);

  endingScene (guess, answer, numGuesses);
}

string checkWord(const string& guess, const string& answer, int MAX_LENGTH) 
{
  string coloredString;

  for (int index = 0; index < MAX_LENGTH; ++index) 
  {
    char guessChar = guess[index];
    char answerChar = answer[index];
    
    if (guessChar == answerChar) 
    {
        coloredString += GREEN + guessChar + RESET;
    } 
    else if (answer.find(guessChar) != string::npos) 
    {
        coloredString += YELLOW + guessChar + RESET;
    } 
    else 
    {
        coloredString += RED + guessChar + RESET;
    }
  }

  return coloredString;
}

void endingScene(string guess, string answer, int numGuesses) 
{
  if (guess == answer) 
  {
    cout << "You won in " << numGuesses << " guesses." <<endl;
  } 
  else 
  {
    cout <<"You lost, The ansnwer was " << answer <<"." <<endl;
  }
}

vector<string> readSolutions(int length) {
    string line;
    vector<string> vec;

    ifstream fin;
    fin.open("C:/Users/jahma/Desktop/Visual Studio Code Work/Projects/solutions.txt");

    while (getline(fin, line)) {
        if (line.length() == length) {
            vec.push_back(line);
        }
    }

    fin.close();

    return vec;
}

vector<string> readGuesses(int length) {
    string line;
    vector<string> vec;

    ifstream fin;
    fin.open("C:/Users/jahma/Desktop/Visual Studio Code Work/Projects/guesses.txt");

    while (getline(fin, line)) {
        if (line.length() == length) {
            vec.push_back(line);
        }
    }

    fin.close();

    return vec;
}
