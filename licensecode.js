/* 
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */


//this calculates the total combinations possible given x numbers and y letters
function calculate(numberCount, letterCount){
    return Math.pow(10, numberCount) * Math.pow(26, letterCount);
}

//calculates an upper bound of symbols used, anything above this will only be worse
function findMaxSymbols(goal) {
    var maxSymbols = 1;
    var maxValue = 10;
    
    while(maxValue < goal) {
        maxSymbols = maxSymbols + 1;
        maxValue = Math.pow(10, maxSymbols);
    }
    return maxSymbols;
}

//set the initial configuration to 1 number and 0 letters
var goal = 0;
var maxSymbols = 0;
var leastExcess = 0;
var totalSymbols = 1;
var numbers = 1;
var letters = 0;
var finished = 0;
var plates = 0;
var excess = 0;

function start(){
    goal = parseInt(document.getElementById('input').value);
    maxSymbols = findMaxSymbols(goal);
    
    //set the initial best outcome to all letters equal to the max symbol count
    bestNumberCount = maxSymbols;
    bestLetterCount = 0;
    leastExcess = Math.pow(10, maxSymbols) - goal;
    
    totalSymbols = 1;
    numbers = 1;
    letters = 0;
    plates = 10;
    excess = 0;
    
    //calculate all combinations of letters and numbers below the maxSymbol 
    //count, only store the combination that are greater than the goal and 
    //have the least excess plates.
    while(totalSymbols < maxSymbols){
        while(numbers >= 0){
            plates = calculate(numbers, letters);
            //if the combination is the best seen so far store it away
            if(plates >= goal){
                excess = plates - goal;
                if(excess < leastExcess){
                    bestNumberCount = numbers;
                    bestLetterCount = letters;
                    leastExcess = excess;
                }
            }
            
            //increment the numbers decrement the symbols
            numbers = numbers - 1;
            letters = letters + 1;
        }
        //next iteration with an added symbol
        totalSymbols = totalSymbols + 1;
        numbers = totalSymbols;
        letters = 0;
    }
    
    //finished, print out the necessary information
    document.getElementById('outputPopulation').innerHTML = goal;
    document.getElementById('outputNumbers').innerHTML = bestNumberCount;
    document.getElementById('outputLetters').innerHTML = bestLetterCount;
    document.getElementById('outputPlates').innerHTML = calculate(bestNumberCount, bestLetterCount);
    document.getElementById('outputExcess').innerHTML = calculate(bestNumberCount, bestLetterCount) - goal;
}




