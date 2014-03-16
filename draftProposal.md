BlackJack
=========

Projet Proposal (Draft)
----

###1. Mandatory Tasks

  * Using true rules according to wikipedia (http://en.wikipedia.org/wiki/Blackjack)
    * Card value (2 to 10 -> facial value, As -> 1 or 11, J Q K -> 10 points)
    * The dealer has one of this two cards hidden
    * Dealer take cards until he hit 17 or more
    * Split (3 max)
    * Double down
    * Insurance
  
  * Few more change
    * Using two decks
    * More efficient shuffling method (Knuth Shuffle http://en.wikipedia.org/wiki/Fisher–Yates_shuffle)
    * Multiplatform
  
  * Simple Online multiplayer
    * Clients/Server architecture
    * One room
    * Up to 5 players
    * Game Start when the first player enter the room
    * New player wait for the current turn to end to play
    * Each player is given a define amount of token when he entrer in the room and lose when he don’t have enough to play anymore

###2. Optionnal Tasks

  * Windowed clients (SDL ?)
  * Advanced Online Multiplayer
    * More than one room
    * Customized room (min/max bid, max player number, password protected)
    * User account to save the token balance
    * Tchat Room
    * Quick Access Room
  * Unit testing
