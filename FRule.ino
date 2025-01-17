void fRule(){
// V2 kipas
// rule1
FuzzyRuleAntecedent *tempCoolAndHumLow1 = new FuzzyRuleAntecedent();
tempCoolAndHumLow1->joinWithAND(cool, low);
FuzzyRuleAntecedent *iftempCoolAndHumLowAndcarbonco2Safe1 = new FuzzyRuleAntecedent();
iftempCoolAndHumLowAndcarbonco2Safe1->joinWithAND(tempCoolAndHumLow1, co2safe);
FuzzyRuleConsequent *thenFanNormal1 = new FuzzyRuleConsequent();
thenFanNormal1->addOutput(normal);
FuzzyRule *fuzzyRule1 = new FuzzyRule (1, iftempCoolAndHumLowAndcarbonco2Safe1, thenFanNormal1);
fuzzy->addFuzzyRule(fuzzyRule1);

//rule2
FuzzyRuleAntecedent *tempCoolAndHumLow2 = new FuzzyRuleAntecedent();
tempCoolAndHumLow2->joinWithAND(cool, low);
FuzzyRuleAntecedent *iftempCoolAndHumLowAndcarbonco2Danger2 = new FuzzyRuleAntecedent();
iftempCoolAndHumLowAndcarbonco2Danger2->joinWithAND(tempCoolAndHumLow1, co2danger);
FuzzyRuleConsequent *thenFanFast2 = new FuzzyRuleConsequent();
thenFanFast2->addOutput(fast);
FuzzyRule *fuzzyRule2 = new FuzzyRule (2, iftempCoolAndHumLowAndcarbonco2Danger2, thenFanFast2);
fuzzy->addFuzzyRule(fuzzyRule2);

//rule3
FuzzyRuleAntecedent *tempCoolAndHumNormal3 = new FuzzyRuleAntecedent();
tempCoolAndHumNormal3->joinWithAND(cool, humnormal);
FuzzyRuleAntecedent *iftempCoolAndHumNormalAndcarbonco2Safe3 = new FuzzyRuleAntecedent();
iftempCoolAndHumNormalAndcarbonco2Safe3 ->joinWithAND(tempCoolAndHumNormal3, co2safe);
FuzzyRuleConsequent *thenFanOff3 = new FuzzyRuleConsequent();
thenFanOff3->addOutput(off);
FuzzyRule *fuzzyRule3 = new FuzzyRule (3, iftempCoolAndHumNormalAndcarbonco2Safe3, thenFanOff3);
fuzzy->addFuzzyRule(fuzzyRule3);

//rule4
FuzzyRuleAntecedent *tempCoolAndHumNormal4 = new FuzzyRuleAntecedent();
tempCoolAndHumNormal4->joinWithAND(cool, humnormal);
FuzzyRuleAntecedent *iftempCoolAndHumNormalAndcarbonco2Danger4 = new FuzzyRuleAntecedent();
iftempCoolAndHumNormalAndcarbonco2Danger4 ->joinWithAND(tempCoolAndHumNormal4, co2danger);
FuzzyRuleConsequent *thenFanFast4 = new FuzzyRuleConsequent();
thenFanFast4->addOutput(fast);
FuzzyRule *fuzzyRule4 = new FuzzyRule (4, iftempCoolAndHumNormalAndcarbonco2Danger4, thenFanFast4);
fuzzy->addFuzzyRule(fuzzyRule4);

//rule 5
FuzzyRuleAntecedent *tempCoolAndHumHigh5 = new FuzzyRuleAntecedent();
tempCoolAndHumHigh5->joinWithAND(cool, high);
FuzzyRuleAntecedent *iftempCoolAndHumHighAndcarbonco2Safe5 = new FuzzyRuleAntecedent();
iftempCoolAndHumHighAndcarbonco2Safe5 ->joinWithAND(tempCoolAndHumHigh5, co2safe);
FuzzyRuleConsequent *thenFanOff5= new FuzzyRuleConsequent();
thenFanOff5->addOutput(off);
FuzzyRule *fuzzyRule5 = new FuzzyRule (5, iftempCoolAndHumHighAndcarbonco2Safe5, thenFanOff5);
fuzzy->addFuzzyRule(fuzzyRule5);

//rule 6
FuzzyRuleAntecedent *tempCoolAndHumHigh6 = new FuzzyRuleAntecedent();
tempCoolAndHumHigh6->joinWithAND(cool, high);
FuzzyRuleAntecedent *iftempCoolAndHumHighAndcarbonco2Danger6= new FuzzyRuleAntecedent();
iftempCoolAndHumHighAndcarbonco2Danger6 ->joinWithAND(tempCoolAndHumHigh6, co2danger);
FuzzyRuleConsequent *thenFanFast6= new FuzzyRuleConsequent();
thenFanFast6->addOutput(fast);
FuzzyRule *fuzzyRule6 = new FuzzyRule (6, iftempCoolAndHumHighAndcarbonco2Danger6 , thenFanFast6);
fuzzy->addFuzzyRule(fuzzyRule6);

//rule 7
FuzzyRuleAntecedent *tempNormalAndHumLow7 = new FuzzyRuleAntecedent();
tempNormalAndHumLow7->joinWithAND(tempnormal, low);
FuzzyRuleAntecedent *iftempNormalAndHumLowAndcarbonco2Safe7= new FuzzyRuleAntecedent();
iftempNormalAndHumLowAndcarbonco2Safe7 ->joinWithAND(tempNormalAndHumLow7, co2safe);
FuzzyRuleConsequent *thenFanNormal7= new FuzzyRuleConsequent();
thenFanNormal7->addOutput(normal);
FuzzyRule *fuzzyRule7 = new FuzzyRule (7, iftempNormalAndHumLowAndcarbonco2Safe7 ,thenFanNormal7);
fuzzy->addFuzzyRule(fuzzyRule7);

//rule 8
FuzzyRuleAntecedent *tempNormalAndHumLow8 = new FuzzyRuleAntecedent();
tempNormalAndHumLow8->joinWithAND(tempnormal, low);
FuzzyRuleAntecedent *iftempNormalAndHumLowAndcarbonco2Danger8= new FuzzyRuleAntecedent();
iftempNormalAndHumLowAndcarbonco2Danger8 ->joinWithAND(tempNormalAndHumLow8, co2danger);
FuzzyRuleConsequent *thenFanFast8= new FuzzyRuleConsequent();
thenFanFast8->addOutput(fast);
FuzzyRule *fuzzyRule8 = new FuzzyRule (8, iftempNormalAndHumLowAndcarbonco2Danger8, thenFanFast8);
fuzzy->addFuzzyRule(fuzzyRule8);

//rule 9
FuzzyRuleAntecedent *tempNormalAndHumNormal9 = new FuzzyRuleAntecedent();
tempNormalAndHumNormal9->joinWithAND(tempnormal, humnormal);
FuzzyRuleAntecedent *iftempNormalAndHumNormalAndcarbonco2Safe9= new FuzzyRuleAntecedent();
iftempNormalAndHumNormalAndcarbonco2Safe9->joinWithAND(tempNormalAndHumNormal9, co2safe);
FuzzyRuleConsequent *thenFanOff9 = new FuzzyRuleConsequent();
thenFanOff9->addOutput(off);
FuzzyRule *fuzzyRule9 = new FuzzyRule (9, iftempNormalAndHumNormalAndcarbonco2Safe9, thenFanOff9);
fuzzy->addFuzzyRule(fuzzyRule9);

//rule 10
FuzzyRuleAntecedent *tempNormalAndHumNormal10 = new FuzzyRuleAntecedent();
tempNormalAndHumNormal10->joinWithAND(tempnormal, humnormal);
FuzzyRuleAntecedent *iftempNormalAndHumNormalAndcarbonco2Danger10= new FuzzyRuleAntecedent();
iftempNormalAndHumNormalAndcarbonco2Danger10->joinWithAND(tempNormalAndHumNormal10, co2danger);
FuzzyRuleConsequent *thenFanFast10 = new FuzzyRuleConsequent();
thenFanFast10->addOutput(fast);
FuzzyRule *fuzzyRule10 = new FuzzyRule (10, iftempNormalAndHumNormalAndcarbonco2Danger10, thenFanFast10);
fuzzy->addFuzzyRule(fuzzyRule10);

//rule 11
FuzzyRuleAntecedent *tempNormalAndHumHigh11 = new FuzzyRuleAntecedent();
tempNormalAndHumHigh11->joinWithAND(tempnormal, high);
FuzzyRuleAntecedent *iftempNormalAndHumHighAndcarbonco2Safe11= new FuzzyRuleAntecedent();
iftempNormalAndHumHighAndcarbonco2Safe11->joinWithAND(tempNormalAndHumHigh11, co2safe);
FuzzyRuleConsequent *thenFanOff11 = new FuzzyRuleConsequent();
thenFanOff11->addOutput(off);
FuzzyRule *fuzzyRule11 = new FuzzyRule (11, iftempNormalAndHumHighAndcarbonco2Safe11, thenFanOff11);
fuzzy->addFuzzyRule(fuzzyRule11);

// rule 12
FuzzyRuleAntecedent *tempNormalAndHumHigh12 = new FuzzyRuleAntecedent();
tempNormalAndHumHigh12->joinWithAND(tempnormal, high);
FuzzyRuleAntecedent *iftempNormalAndHumHighAndcarbonco2Danger12= new FuzzyRuleAntecedent();
iftempNormalAndHumHighAndcarbonco2Danger12->joinWithAND(tempNormalAndHumHigh12, co2danger);
FuzzyRuleConsequent *thenFanFast12 = new FuzzyRuleConsequent();
thenFanFast12->addOutput(fast);
FuzzyRule *fuzzyRule12 = new FuzzyRule (12, iftempNormalAndHumHighAndcarbonco2Danger12, thenFanFast12);
fuzzy->addFuzzyRule(fuzzyRule12);

//rule 13
FuzzyRuleAntecedent *tempHotAndHumLow13 = new FuzzyRuleAntecedent();
tempHotAndHumLow13->joinWithAND(hot, low);
FuzzyRuleAntecedent *iftempHotAndHumLowAndCarbonco2Safe13= new FuzzyRuleAntecedent();
iftempHotAndHumLowAndCarbonco2Safe13->joinWithAND(tempHotAndHumLow13, co2safe);
FuzzyRuleConsequent *thenFanFast13 = new FuzzyRuleConsequent();
thenFanFast13->addOutput(fast);
FuzzyRule *fuzzyRule13 = new FuzzyRule (13, iftempHotAndHumLowAndCarbonco2Safe13, thenFanFast13);
fuzzy->addFuzzyRule(fuzzyRule13);

//rule 14
FuzzyRuleAntecedent *tempHotAndHumLow14 = new FuzzyRuleAntecedent();
tempHotAndHumLow14->joinWithAND(hot, low);
FuzzyRuleAntecedent *iftempHotAndHumLowAndCarbonco2Danger14= new FuzzyRuleAntecedent();
iftempHotAndHumLowAndCarbonco2Danger14->joinWithAND(tempHotAndHumLow14, co2danger);
FuzzyRuleConsequent *thenFanFast14 = new FuzzyRuleConsequent();
thenFanFast14->addOutput(fast);
FuzzyRule *fuzzyRule14 = new FuzzyRule (14, iftempHotAndHumLowAndCarbonco2Danger14, thenFanFast14);
fuzzy->addFuzzyRule(fuzzyRule14);

//rule 15
FuzzyRuleAntecedent *tempHotAndHumNormal15 = new FuzzyRuleAntecedent();
tempHotAndHumNormal15->joinWithAND(hot, humnormal);
FuzzyRuleAntecedent *iftempHotAndHumNormalAndCarbonco2Safe15= new FuzzyRuleAntecedent();
iftempHotAndHumNormalAndCarbonco2Safe15->joinWithAND(tempHotAndHumNormal15, co2safe);
FuzzyRuleConsequent *thenFanFast15 = new FuzzyRuleConsequent();
thenFanFast15->addOutput(fast);
FuzzyRule *fuzzyRule15 = new FuzzyRule (15, iftempHotAndHumNormalAndCarbonco2Safe15, thenFanFast15);
fuzzy->addFuzzyRule(fuzzyRule15);

//rule 16
FuzzyRuleAntecedent *tempHotAndHumNormal16 = new FuzzyRuleAntecedent();
tempHotAndHumNormal16->joinWithAND(hot, humnormal);
FuzzyRuleAntecedent *iftempHotAndHumNormalAndCarbonco2Danger16= new FuzzyRuleAntecedent();
iftempHotAndHumNormalAndCarbonco2Danger16->joinWithAND(tempHotAndHumNormal16, co2danger);
FuzzyRuleConsequent *thenFanFast16 = new FuzzyRuleConsequent();
thenFanFast16->addOutput(fast);
FuzzyRule *fuzzyRule16 = new FuzzyRule (16, iftempHotAndHumNormalAndCarbonco2Danger16, thenFanFast16);
fuzzy->addFuzzyRule(fuzzyRule16);

//rule 17
FuzzyRuleAntecedent *tempHotAndHumHigh17 = new FuzzyRuleAntecedent();
tempHotAndHumHigh17->joinWithAND(hot, high);
FuzzyRuleAntecedent *iftempHotAndHumHighAndCarbonco2Safe17= new FuzzyRuleAntecedent();
iftempHotAndHumHighAndCarbonco2Safe17->joinWithAND(tempHotAndHumHigh17, co2safe);
FuzzyRuleConsequent *thenFanNormal17 = new FuzzyRuleConsequent();
thenFanNormal17->addOutput(normal);
FuzzyRule *fuzzyRule17 = new FuzzyRule (17, iftempHotAndHumHighAndCarbonco2Safe17, thenFanNormal17);
fuzzy->addFuzzyRule(fuzzyRule17);

//rule 18
FuzzyRuleAntecedent *tempHotAndHumHigh18 = new FuzzyRuleAntecedent();
tempHotAndHumHigh18->joinWithAND(hot, high);
FuzzyRuleAntecedent *iftempHotAndHumHighAndCarbonco2Danger18= new FuzzyRuleAntecedent();
iftempHotAndHumHighAndCarbonco2Danger18->joinWithAND(tempHotAndHumHigh18, co2danger);
FuzzyRuleConsequent *thenFanFast18 = new FuzzyRuleConsequent();
thenFanFast18->addOutput(fast);
FuzzyRule *fuzzyRule18 = new FuzzyRule (18, iftempHotAndHumHighAndCarbonco2Danger18, thenFanFast18);
fuzzy->addFuzzyRule(fuzzyRule18);

//pompa 
//rule 1
FuzzyRuleAntecedent *tempCoolAndHumLow = new FuzzyRuleAntecedent();
tempCoolAndHumLow->joinWithAND(cool, low);

FuzzyRuleConsequent *thenPompaLama1 = new FuzzyRuleConsequent();
thenPompaLama1->addOutput(lama);

FuzzyRule *fuzzyRule19 = new FuzzyRule(19, tempCoolAndHumLow, thenPompaLama1);
fuzzy->addFuzzyRule(fuzzyRule19);

//rule 2
FuzzyRuleAntecedent *tempCoolAndHumNormal = new FuzzyRuleAntecedent();
tempCoolAndHumNormal->joinWithAND(cool, humnormal);

FuzzyRuleConsequent *thenPompaMati2 = new FuzzyRuleConsequent();
thenPompaMati2->addOutput(mati);

FuzzyRule *fuzzyRule20 = new FuzzyRule(20, tempCoolAndHumNormal, thenPompaMati2);
fuzzy->addFuzzyRule(fuzzyRule20);

//rule 3
FuzzyRuleAntecedent *tempCoolAndHumHigh = new FuzzyRuleAntecedent();
tempCoolAndHumHigh->joinWithAND(cool, high);

FuzzyRuleConsequent *thenPompaMati3 = new FuzzyRuleConsequent();
thenPompaMati3->addOutput(mati);

FuzzyRule *fuzzyRule21 = new FuzzyRule(21, tempCoolAndHumHigh, thenPompaMati3);
fuzzy->addFuzzyRule(fuzzyRule21);

//rule 4
FuzzyRuleAntecedent *tempNormalAndHumLow = new FuzzyRuleAntecedent();
tempNormalAndHumLow->joinWithAND(tempnormal, low);

FuzzyRuleConsequent *thenPompaSingkat4 = new FuzzyRuleConsequent();
thenPompaSingkat4->addOutput(singkat);

FuzzyRule *fuzzyRule22 = new FuzzyRule(22, tempNormalAndHumLow, thenPompaSingkat4);
fuzzy->addFuzzyRule(fuzzyRule22);

//rule 5
FuzzyRuleAntecedent *tempNormalAndHumNormal = new FuzzyRuleAntecedent();
tempNormalAndHumNormal->joinWithAND(tempnormal, humnormal);

FuzzyRuleConsequent *thenPompaMati5 = new FuzzyRuleConsequent();
thenPompaMati5->addOutput(mati);

FuzzyRule *fuzzyRule23 = new FuzzyRule(23, tempNormalAndHumNormal, thenPompaMati5);
fuzzy->addFuzzyRule(fuzzyRule23);

//rule 6
FuzzyRuleAntecedent *tempNormalAndHumHigh = new FuzzyRuleAntecedent();
tempNormalAndHumHigh ->joinWithAND(tempnormal, high);

FuzzyRuleConsequent *thenPompaMati6 = new FuzzyRuleConsequent();
thenPompaMati6->addOutput(mati);

FuzzyRule *fuzzyRule24 = new FuzzyRule(24, tempNormalAndHumHigh, thenPompaMati6);
fuzzy->addFuzzyRule(fuzzyRule24);

//rule 7
FuzzyRuleAntecedent *tempHotAndHumLow = new FuzzyRuleAntecedent();
tempHotAndHumLow->joinWithAND(hot, low);

FuzzyRuleConsequent *thenPompaLama7 = new FuzzyRuleConsequent();
thenPompaLama7->addOutput(lama);

FuzzyRule *fuzzyRule25 = new FuzzyRule(25, tempHotAndHumLow, thenPompaLama7);
fuzzy->addFuzzyRule(fuzzyRule25);

//rule 8
FuzzyRuleAntecedent *tempHotAndHumNormal = new FuzzyRuleAntecedent();
tempHotAndHumNormal->joinWithAND(hot, humnormal);

FuzzyRuleConsequent *thenPompaSingkat8 = new FuzzyRuleConsequent();
thenPompaSingkat8->addOutput(singkat);

FuzzyRule *fuzzyRule26 = new FuzzyRule(26, tempHotAndHumNormal, thenPompaSingkat8);
fuzzy->addFuzzyRule(fuzzyRule26);

//rule 9
FuzzyRuleAntecedent *tempHotAndHumHigh = new FuzzyRuleAntecedent();
tempHotAndHumHigh->joinWithAND(hot, high);

FuzzyRuleConsequent *thenPompaSingkat9 = new FuzzyRuleConsequent();
thenPompaSingkat9->addOutput(singkat); 

FuzzyRule *fuzzyRule27 = new FuzzyRule(27, tempHotAndHumHigh, thenPompaSingkat9);
fuzzy->addFuzzyRule(fuzzyRule27);

}