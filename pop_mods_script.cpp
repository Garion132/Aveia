#include<iostream>
#include<fstream>
#include<sstream>
using namespace std;

//Stats for Population, each per 1000
const static float RURAL_TAX = 0.034f;
const static float RURAL_GOODS_PROD = 0.005f;
const static float RURAL_MANPOWER = 0.1f;
const static float RURAL_SAILORS = 0.01f;
const static float RURAL_TRADE_POWER = 0.003f;

const static float URBAN_TAX = 0.05f;
const static float URBAN_GOODS_PROD = 0.01f;
const static float URBAN_MANPOWER = 0.075f;
const static float URBAN_SAILORS = 0.025f;
const static float URBAN_TRADE_POWER = 0.06f;


static void newRuralEntry(string &list, string &loc, string &code, string &clear, int pop, int stepSize){
    char buffer [33];
    string cd = "", cl = "";
    string popS = itoa(pop,buffer,10);
    string name = popS + "_rural_pop_modifier";
    ostringstream os;
    os.precision(3);

    os << endl;
    os << name << " = {" << endl;
    if(RURAL_TAX > 0 && pop > 0) os << "\ttax_income = " << (RURAL_TAX * pop / 1000) << endl;
    if(RURAL_GOODS_PROD > 0 && pop > 0) os << "\ttrade_goods_size = " << (RURAL_GOODS_PROD * pop / 1000) << endl;
    if(RURAL_MANPOWER > 0 && pop > 0) os << "\tlocal_manpower = " << (RURAL_MANPOWER * pop / 1000) << endl;
    if(RURAL_SAILORS > 0 && pop > 0) os << "\tlocal_sailors = " << (RURAL_SAILORS * pop / 1000) << endl;
    if(RURAL_TRADE_POWER > 0 && pop > 0) os << "\tprovince_trade_power_value = " << (RURAL_TRADE_POWER * pop / 1000) << endl;
    os << "}";
    list += os.str();
    
    if(pop == 0){
        loc += name + ":0 \"Insignificant Rural Population\"\n";

        cd += "\telse = {\n";
        cd += "\t\tadd_permanent_province_modifier = { name = " + name + " duration = -1 }\n";
        cd += "\t}\n";
        code = cd + code;

        cl += "\telse_if = { limit = { has_province_modifier = " + name + " }\n";
        cl += "\t\tremove_province_modifier = " + name + "\n";
        cl += "\t}\n";
        clear = cl + clear;
    }
    else{
        loc += name + ":0 \"" + popS + " Rural Population\"\n";

        cd += "\telse_if = { limit = { check_variable = { which = rural_pop value = " + to_string(float(pop)/1000) + " } }\n";
        cd += "\t\tadd_permanent_province_modifier = { name = " + name + " duration = -1 }\n";
        cd += "\t}\n";
        code = cd + code;

        cl += "\telse_if = { limit = { has_province_modifier = " + name + " }\n";
        cl += "\t\tremove_province_modifier = " + name + "\n";
        cl += "\t}\n";
        clear = cl + clear;
    }
    loc += "desc_" + name + ":0 \"Rural Population: [THIS.rural_pop.GetValue]\"\n";

}


static void newUrbanEntry(string &list, string &loc, string &code, string &clear, int pop, int stepSize){
    char buffer [33];
    string cd = "", cl = "";
    string popS = itoa(pop,buffer,10);
    string name = popS + "_urban_pop_modifier";
    ostringstream os;
    os.precision(3);

    os << endl;
    os << name << " = {" << endl;
    if(URBAN_TAX > 0 && pop > 0) os << "\ttax_income = " << (URBAN_TAX * pop / 1000) << endl;
    if(URBAN_GOODS_PROD > 0 && pop > 0) os << "\ttrade_goods_size = " << (URBAN_GOODS_PROD * pop / 1000) << endl;
    if(URBAN_MANPOWER > 0 && pop > 0) os << "\tlocal_manpower = " << (URBAN_MANPOWER * pop / 1000) << endl;
    if(URBAN_SAILORS > 0 && pop > 0) os << "\tlocal_sailors = " << (URBAN_SAILORS * pop / 1000) << endl;
    if(URBAN_TRADE_POWER > 0 && pop > 0) os << "\tprovince_trade_power_value = " << (URBAN_TRADE_POWER * pop / 1000) << endl;
    os << "}";
    list += os.str();
    
    if(pop == 0){
        loc += name + ":0 \"Insignificant Urban Population\"\n";

        cd += "\telse = {\n";
        cd += "\t\tadd_permanent_province_modifier = { name = " + name + " duration = -1 }\n";
        cd += "\t}\n";
        code = cd + code;

        cl += "\telse_if = { limit = { has_province_modifier = " + name + " }\n";
        cl += "\t\tremove_province_modifier = " + name + "\n";
        cl += "\t}\n";
        clear = cl + clear;
    }
    else{
        loc += name + ":0 \"" + popS + " Urban Population\"\n";

        cd += "\telse_if = { limit = { check_variable = { which = urban_pop value = " + to_string(float(pop)/1000) + " } }\n";
        cd += "\t\tadd_permanent_province_modifier = { name = " + name + " duration = -1 }\n";
        cd += "\t}\n";
        code = cd + code;

        cl += "\telse_if = { limit = { has_province_modifier = " + name + " }\n";
        cl += "\t\tremove_province_modifier = " + name + "\n";
        cl += "\t}\n";
        clear = cl + clear;
    }
    loc += "desc_" + name + ":0 \"Urban Population: [THIS.urban_pop.GetValue]\"\n";
}

int main(int argc, char *argv[]){
    
    string file = "";
    ofstream of;
    
    if(argc>=2){
        file = argv[1];
    }
    else{
        file = "output.txt";
    }

    of.open(file); //Open File
    if(!of.is_open()){
        cerr << "Error while opening file " << file << endl;
        return 1;
    }

    //Inputs
    string input;
    int popStep, ruralMax, urbanMax;

    cout << "Population Size per Step (in 1s, integer values only): ";
    cin >> input;
    popStep = stoi(input);
    cout << "Storing result as " << popStep << endl;
    
    cout << "Maximum Rural Population (in 1000s, integer values only): ";
    cin >> input;
    ruralMax = stoi(input);
    cout << "Storing result as " << ruralMax << "K" << endl;
    
    cout << "Maximum Urban Population (in 1000s, integer values only): ";
    cin >> input;
    urbanMax = stoi(input);
    cout << "Storing result as " << urbanMax << "K" << endl;

    cout << "Creating File..." << endl << endl;

    //Rural
    string rpopString = "";
    string rpopLoc = "";
    string rpopCode = "";
    string rpopClear = "";
    int currentPop = 0;
    while(currentPop <= ruralMax*1000){
        newRuralEntry(rpopString, rpopLoc, rpopCode, rpopClear, currentPop, popStep);
        currentPop += popStep;
    }
    rpopCode = "update_rural_pop_modifiers = {\n\tclear_rural_pop_modifiers = yes\n" + rpopCode + "}\n";
    rpopClear = "clear_rural_pop_modifiers = {\n" + rpopClear + "}\n";
    cout << "Rural Population Done." << endl;

    //Urban
    string upopString = "";
    string upopLoc = "";
    string upopCode = "";
    string upopClear = "";
    currentPop = 0;
    while(currentPop <= urbanMax*1000){
        newUrbanEntry(upopString, upopLoc, upopCode, upopClear, currentPop, popStep);
        currentPop += popStep;
    }
    upopCode = "update_urban_pop_modifiers = {\n\tclear_urban_pop_modifiers = yes\n" + upopCode + "}\n";
    upopClear = "clear_urban_pop_modifiers = {\n" + upopClear + "}\n";
    cout << "Urban Population Done." << endl;

    of << "#Rural Population" << endl;
    of << rpopString << endl;
    of << "#Urban Population" << endl;
    of << upopString << endl << endl;
    of << "#Rural Pop Create Code" << endl;
    of << rpopCode << endl;
    of << "#Rural Pop Clear Code" << endl;
    of << rpopClear << endl;
    of << "#Urban Pop Create Code" << endl;
    of << upopCode << endl;
    of << "#Urban Pop Clear Code" << endl;
    of << upopClear << endl;
    of << "#Localization" << endl;
    of << rpopLoc << endl << upopLoc << endl;
    of.close();
}