#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define BUFFER_SIZE 20

typedef enum { NONE, GRASS, FIRE, WATER } PokemonType;

struct pokemon {
    char name[BUFFER_SIZE];
    char ability[BUFFER_SIZE];
    int health;
    PokemonType type;
};

typedef struct pokemon Pokemon;

int menu(void);

Pokemon select_pokemon(void);
int check_type(PokemonType att, PokemonType def);
int attack(Pokemon *att, Pokemon *def);
void make_pokemon(Pokemon *p, int selection);
void print_pokemon(Pokemon *p);

int main()
{
    srand(time(NULL));
    Pokemon squirtle = { "Squirtle", "Water Gun", 50, WATER };
    Pokemon charmander = { "Charmander", "Ember", 50, FIRE };
    Pokemon bulbasaur = { "Bulbasaur", "Vine Whip", 50, GRASS };
    Pokemon *attacker = &squirtle;
    Pokemon *defender = &charmander;
    Pokemon *temp;
    int battle_result = 0;
    while (battle_result == 0) {
        print_pokemon(attacker);
        print_pokemon(defender);
        battle_result = attack(attacker, defender);
        temp = attacker;
        attacker = defender;
        defender = temp;
    }
    
}

int menu(void)
{
    char buffer[BUFFER_SIZE];
    int option;
    do {
        printf("Low-budget Pokemon\n\n"
               "Please choose an option:\n"
               "1. Battle!\n"
               "2. View Pokemon\n"
               "3. Quit\n"
               "> ");
        fgets(buffer, BUFFER_SIZE, stdin);
        if (sscanf(buffer, "%d", &option) != 1) {
            printf("Invalid input! Try again.\n");
        }
        else if ((option < 1) || (option > 3)) {
            printf("Invalid input! Try again.\n");
        }
    } while ((option < 1) || (option > 3));

    return option;
}

Pokemon select_pokemon(void)
{
    Pokemon p;
    char buffer[BUFFER_SIZE];
    int option;
    do {
        printf("Select a Pokemon:\n"
               "1. Squirtle\n"
               "2. Bulbasaur\n"
               "3. Charmander\n"
               "> ");
        fgets(buffer, BUFFER_SIZE, stdin);
        if (sscanf(buffer, "%d", &option) != 1) {
            printf("Invalid input! Try again.\n");
        }
        else if ((option < 1) || (option > 3)) {
            printf("Invalid input! Try again.\n");
        }
    } while ((option < 1) || (option > 3));

    switch (option) {
    case 1:
        strcpy(p.name, "Squirtle");
        strcpy(p.ability, "Water Gun");
        p.health = 50;
        p.type = WATER;
        break;
    case 2:
        strcpy(p.name, "Bulbasaur");
        strcpy(p.ability, "Vine Whip");
        p.health = 50;
        p.type = GRASS;
        break;
    case 3:
        strcpy(p.name, "Charmander");
        strcpy(p.ability, "Ember");
        p.health = 50;
        p.type = FIRE;
        break;
    default:
        strcpy(p.name, "MISSINGNO");
        strcpy(p.ability, "asdfasfasb");
        p.health = 50;
        p.type = NONE;
        break;
    }

    return p;
}

int check_type(PokemonType att, PokemonType def)
{
    if (att == def) {
        return -1;
    }
    switch(att) {
    case GRASS:
        if (def == FIRE) {
            return -1;
        }
        else if (def == WATER) {
            return 1;
        }
        break;
    case WATER:
        if (def == GRASS) {
            return -1;
        }
        else if (def == FIRE) {
            return 1;
        }
        break;
    case FIRE:
        if (def == WATER) {
            return -1;
        }
        else if (def == GRASS) {
            return 1;
        }
        break;
    default:
        break;
    }
    return 0;
}

int attack(Pokemon *att, Pokemon *def)
{
    printf("%s used %s!\n", att->name, att->ability);
    while(getchar() != '\n');
    int modifier = check_type(att->type, def->type);
    int damage = 1 + (rand() % 10);
    switch(modifier) {
    case 0:
        break;
    case -1:
        printf("It's not very effective...\n");
        damage /= 2;
        break;
    case 1:
        printf("It's super-effective!\n");
        damage *= 2;
        break;
    default:
        break;
    }
    printf("Deals %d damage\n", damage);
    while(getchar() != '\n');
    
    def->health -= damage;
    if (def->health <= 0) {
        printf("%s fainted!\n", def->name);
        while(getchar() != '\n');
        return 1;
    }
    return 0;
}

void print_pokemon(Pokemon *p)
{
    printf("%s: %d HP\n", p->name, p->health);
}
