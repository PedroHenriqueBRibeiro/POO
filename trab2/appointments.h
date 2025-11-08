#ifndef APPOINTMENTS_H
#define APPOINTMENTS_H

#include <string>
#include "datetime.h"

enum class Tipo { AULA = 0, ORIENT = 1, REUNIAO = 2, EVENTO = 3, PARTICULAR = 4 };

int base_factor(Tipo t);
int tipo_rank_for_tiebreak(Tipo t);

class Appointment {
public:
    Tipo tipo;
    int id = 0;
    DateTime ini{}, fim{};
    int dur_min = 0;
    int grau_prior = 0;
    bool adiavel = false;
    std::string descricao;
    int forced_by = -1;

    virtual ~Appointment() = default;
    virtual int  factor() const = 0;
    virtual bool isAdiavel() const = 0;
    virtual void describe() = 0;
    virtual void dataFull(std::string& out) const = 0;

    int priority() const { return grau_prior * factor(); }
};

class Aula : public Appointment {
public:
    std::string disciplina, nivel;
    Aula() { tipo = Tipo::AULA; }
    int  factor() const override { return 2; }
    bool isAdiavel() const override { return false; }
    void describe() override { descricao = "Aula de " + disciplina; }
    void dataFull(std::string& out) const override { out = disciplina; }
};

class Orient : public Appointment {
public:
    std::string aluno, nivel, assunto;
    Orient() { tipo = Tipo::ORIENT; }
    int  factor() const override { int f = base_factor(tipo); if (!adiavel) f += 1; return f; }
    bool isAdiavel() const override { return adiavel; }
    void describe() override { descricao = "Orientação de " + aluno; }
    void dataFull(std::string& out) const override { out = aluno; }
};

class Reuniao : public Appointment {
public:
    std::string assunto;
    Reuniao() { tipo = Tipo::REUNIAO; }
    int  factor() const override { int f = base_factor(tipo); if (!adiavel) f += 1; return f; }
    bool isAdiavel() const override { return adiavel; }
    void describe() override { descricao = "Reunião de Departamento"; }
    void dataFull(std::string& out) const override { out = "Reunião de Departamento"; }
};

class Evento : public Appointment {
public:
    std::string nome, local; int dur_dias = 0;
    Evento() { tipo = Tipo::EVENTO; }
    int  factor() const override { return 3; }
    bool isAdiavel() const override { return false; }
    void describe() override { descricao = nome; }
    void dataFull(std::string& out) const override { out = nome; }
};

class Particular : public Appointment {
public:
    std::string motivo, local;
    Particular() { tipo = Tipo::PARTICULAR; }
    int  factor() const override { int f = base_factor(tipo); if (!adiavel) f += 1; return f; }
    bool isAdiavel() const override { return adiavel; }
    void describe() override { descricao = motivo; }
    void dataFull(std::string& out) const override { out = motivo; }
};

#endif