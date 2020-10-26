#pragma once
#ifndef MAIN_H
#define MAIN_H
#include <iostream>
#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include "Hero.h"

#pragma region inventory characters
wchar_t otherChars[3][3]{
	{L'\x250f', L'\x252f', L'\x2513'},
	{L'\x2517', L'\x2537', L'\x251b'},
	{L'\x2503', L'\x2501', L'\x2502'}
};
/*wchar_t otherChars[3][3]{
	{'┏', '┯', '┓'},
	{'┗', '┷', '┛'},
	{'┃', '━', '│'}
};*/
#pragma endregion
wstring triviaInitial[30][7] = {
	{L"A",L"a",L"Which Disney film has a rabbit named Thumper?",L"A: bambi",L"B: lion king",L"C: fox and the hound",L"D: nemo"},
	{L"A",L"d",L"What color is sully in monsters inc?" ,L"A: mike",L"B: wazowski",L"C: green",L"D: blue"},
	{L"A",L"c",L"What kind of a dog is pongo?",L"A: chihuahua",L"B: terrier",L"C: dalmation",L"D: shephard"},
	{L"A",L"d",L"In the movie \"Robin Hood\" what kind of animal was the Sheriff of Nottingham?",L"A: camel",L"B: bull",L"C: horse",L"D: wolf"},
	{L"A",L"a",L"In the movie \"Toy Story\" what is the name of the kid who owns Buzz?",L"A: andy",L"B: carl",L"C: dave",L"D: gary"},
	{L"A",L"b",L"What is Sleeping Beauty's name?",L"A: sleeping",L"B: aurora",L"C: jasmine",L"D: beauty"},
	{L"A",L"b",L"What kind of animal does Princess Jasmine have for a pet?",L"A: lion",L"B: tiger",L"C: leopard",L"D: cheetah"},
	{L"A",L"c",L"In the movie \"The Lion King\" what is the name of simba's uncle?",L"A: pumba",L"B: timone",L"C: scar",L"D: eric"},
	{L"A",L"b",L"In the movie \"Peter Pan,\" what color dress does tinker bell wear?",L"A: red",L"B: green",L"C: pink",L"D: cyan"},
	{L"A",L"d",L"Which Disney movie features the song \"I Won't Say I'm in Love\"?",L"A: peter pan",L"B: snow white",L"C: princess and the frog",L"D: hercules"},
	{L"A",L"b",L"What is the name of the man that carves Pinocchio?",L"A: gary",L"B: gepetto",L"C: franchesco",L"D: enrique"},
	{L"A",L"b",L"What is the name of the old man in the Disney film \"Up\"?",L"A: gary",L"B: carl",L"C: herbert",L"D: franklin"},
	{L"A",L"c",L"In the Disney movie \"The Rescuers,\" what kind of animal is Bernard?",L"A: rat",L"B: cat",L"C: mouse",L"D: bird"},
	{L"A",L"b",L"In the Disney movie \"The Sword and the Stone,\" what does King Arthur's foster family call him?",L"A: arty",L"B: wart",L"C: tiny",L"D: gelt"},
	{L"A",L"c",L"The sea witch in \"The Little Mermaid\" is half what?",L"A: fish",L"B: fat",L"C: octopus",L"D: eel"},
	{L"A",L"d",L"What do Aladdin and his monkey Abu steal from the marketplace when you are first introduced to them in the movie?",L"A: fish",L"B: nuts",L"C: spices",L"D: bread"},
	{L"A",L"a",L"What popular Disney character makes an appearance as a stuffed animal in Frozen?",L"A: mickey",L"B: donald",L"C: goofy",L"D: pluto"},
	{L"A",L"b",L"Who was the first disney princess?",L"A: sleeping beauty",L"B: snow white",L"C: fiona",L"D: rapunzel"},
	{L"A",L"c",L"What does the enchanted cake in Brave turn Merida's mother into?",L"A: deer",L"B: wolf",L"C: bear",L"D: goat"},
	{L"A",L"a",L"In The Little Mermaid, what name does Ursula go by when she disguises herself and uses Ariel's voice to try and win over Eric?",L"A: vanessa",L"B: elise",L"C: shelly",L"D: maria"},
	{L"A",L"b",L"Who did Pocahontas' father want her to marry?",L"A: tormund",L"B: kocoum",L"C: john",L"D: lewis"},
	{L"A",L"d",L"Which Disney princess is based on a real person?",L"A: belle",L"B: jasmine",L"C: aurora",L"D: pocahontas"},
	{L"A",L"b",L"What is the name of Mulan's pet dragon?",L"A: crickie",L"B: mushu",L"C: poof poof",L"D: stitch"},
	{L"A",L"d",L"What is the name of the song that Cinderella and Prince Charming dance to at the ball?",L"A: all i know",L"B: i want to know what love is",L"C: funky town",L"D: so this is love"},
	{L"A",L"a",L"Flynn Rider is wanted because he is a?",L"A: thief",L"B: killer",L"C: runaway",L"D: smuggler"},
	{L"A",L"d",L"How many daughters does King Titon have?",L"A: four",L"B: three",L"C: six",L"D: seven"},
	{L"A",L"c",L"What does dumbo hold in his trunk that helps him fly?",L"A: a pair of shoes",L"B: wings",L"C: a feather",L"D: hope"},
	{L"A",L"b",L"What is the name of Maleficent's pet raven?",L"A: dekar",L"B: diablo",L"C: edgar",L"D: gloom"},
	{L"A",L"a",L"Where on Scar's face is the scar?",L"A: left eye",L"B: right eye",L"C: 4head",L"D: chin"},
	{L"A",L"c",L"How many brothers does hans have?",L"A: 8",L"B: 10",L"C: 12",L"D: 14"},
};
wstring trivia[30][6];
enum answers { A, B, C, D };
int triviaIndex = 0;
void printGrid(bool, Hero*, Map*);
wstring sadpepe[] = {
	{L"          ████████     ██████"},
	{L"         █░░░░░░░░██ ██░░░░░░█"},
	{L"        █░░░░░░░░░░░█░░░░░░░░░█"},
	{L"       █░░░░░░░███░░░█░░░░░░░░░█"},
	{L"       █░░░░███░░░███░█░░░████░█"},
	{L"      █░░░██░░░░░░░░███░██░░░░██"},
	{L"     █░░░░░░░░░░░░░░░░░█░░░░░░░░███"},
	{L"    █░░░░░░░░░░░░░██████░░░░░████░░█"},
	{L"    █░░░░░░░░░█████░░░████░░██░░██░░█░"},
	{L"   ██░░░░░░░███░░░░░░░░░░█░░░░░░░░███"},
	{L"  █░░░░░░░░░░░░░░█████████░░█████████"},
	{L" █░░░░░░░░░░██████ █  ███████ █  ████"},
	{L" █░░░░░░░░░░█████ █  █ █████ █  █ ████"},
	{L"█░░░░░░░░░░░░█████    ███████    █████"},
	{L"░░░░░░░░░░░░░█████████░░░████████░░░█"},
	{L"░░░░░░░░░░░░░██░░░░░░░█░░░░░░░░░░░░█"},
	{L"░░░░░░░░░░░░░█░░░░░░██░░░░█░░░░░░██"},
	{L"░░░░░░░░░░░░░█░░░░██░░░░░░░███████"},
	{L"░░░░░░░░░░░░░░░░██░░░░░░░░░░█░░░░░█"},
	{L"░░░░░░░░░░░░░█░░░░░░░░░░░░░░░░░░░░░█"},
	{L"░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░█"},
	{L"░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░█"},
	{L"░░░░░░░░░░░█████████░░░░░░░░░░░░░░██"},
	{L"░░░░░░░░░░█▒▒▒▒▒▒▒▒███████████████▒▒█"},
	{L"░░░░░░░░░█▒▒███████▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒█"},
	{L"░░░░░░░░░█▒▒▒▒▒▒▒▒▒█████████████████"},
	{L"░░░░░░░░░░████████▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒█"},
	{L"░░░░░░░░░░░░░░░░░░██████████████████"},
	{L"░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░█"},
	{L"██░░░░░░░░░░░░░░░░░░░░░░░░░░░██"},
	{L"▓██░░░░░░░░░░░░░░░░░░░░░░░░██"},
	{L"▓▓▓███░░░░░░░░░░░░░░░░░░░░█"},
	{L"▓▓▓▓▓▓███░░░░░░░░░░░░░░░██"},
	{L"▓▓▓▓▓▓▓▓▓███████████████▓▓█"},
	{L"▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓██"},
	{L"▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓█"},
	{L"▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓█"}
};
wstring poggers[] = {
{L"$$$$$$$\\"},
{L"$$  __$$\\"},
{L"$$ |  $$ |  $$$$$$\\    $$$$$$\\  $$$$$$\\   $$$$$$\\   $$$$$$\\   $$$$$$$\\"},
{L"$$$$$$$	 | $$  __$$\\ $$  __$$\\ $$  __$$\\ $$  __$$\\ $$  __$$\\ $$  _____|"},
{L"$$  ____/  $$ /  $$ |$$ /  $$ |$$ /  $$ |$$$$$$$$ |$$ |  \\__|\\$$$$$$\\"},
{L"$$ |       $$ |  $$ |$$ |  $$ |$$ |  $$ |$$   ____|$$ |       \\____$$\\"},
{L"$$ |       \\$$$$$$  |\\$$$$$$$ |\\$$$$$$$ |\\$$$$$$$\\ $$ |       $$$$$$$ |"},
{L"\\__|        \\______/  \\____$$ | \\____$$ | \\_______|\\__|       \\_______/"},
{L"                     $$\\   $$ |$$\\   $$ |"},
{L"                      \\$$$$$$ |\\$$$$$$  |"},
{L"                       \\______/ \\______/"}
};
#endif