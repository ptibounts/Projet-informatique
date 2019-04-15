#include <iostream>
#include <queue>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include "arete.h"

Arete::Arete(std::string id,int cout1,int cout2):m_id{id},m_cout1{cout1},m_cout2{cout2}
{
}
/*
void Arete::ajouterCout(const Arete* cout1, const Arete* cout2){
    m_cout1.push_back(cout1);
    m
}
*/
Arete::~Arete()
{
    //dtor
}
