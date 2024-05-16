# Faceit-Helper
It is a old project I made years ago finds the match between nickname of desired player and you. The need for this is that Faceit only provides the nickname of toxic or cheater player you faced before in notifications but doesn't specify exact match you faced. 
So this is a basic web scripting and parsing project that no brainer to do by C++. C++ was used for arbitrary reasons. Python or any other scripting language would be better option.

Algorithm used in _find() function is kinda brute-force, it would be easily optimised.

Coded in CS:GO era so some changes need to be done to work.

## Prerequisites
* C++20
* CMake
* curlpp (used for sending requests)
* nlohmann/json (used for parsing)
