void fSet(){
FuzzyInput *temp = new FuzzyInput(1);
temp->addFuzzySet(cool);
temp->addFuzzySet(tempnormal);
temp->addFuzzySet(hot);
fuzzy->addFuzzyInput(temp);

//Fuzzy input kelembaban
FuzzyInput *hum = new FuzzyInput(2);
hum->addFuzzySet(low);
hum->addFuzzySet(humnormal);
hum->addFuzzySet(high);
fuzzy->addFuzzyInput(hum);

// Fuzzy input co2
FuzzyInput *carbon = new FuzzyInput(3);
carbon->addFuzzySet(co2safe);
carbon->addFuzzySet(co2danger);
fuzzy->addFuzzyInput(carbon);

// Fuzzy output kipas
FuzzyOutput *fan = new FuzzyOutput(1);
fan->addFuzzySet(off);
fan->addFuzzySet(normal);
fan->addFuzzySet(fast);
fuzzy->addFuzzyOutput(fan);

//fuzzy output nozzle
FuzzyOutput *pompa = new FuzzyOutput(2);
pompa->addFuzzySet(mati);
pompa->addFuzzySet(singkat);
pompa->addFuzzySet(lama);
fuzzy->addFuzzyOutput(pompa);

}