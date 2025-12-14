#ifndef PETOBSERVER_H
#define PETOBSERVER_H

class Pet;

class PetObserver
{
public:
    virtual ~PetObserver() = default;
    virtual void onPetChanged(Pet* pet) = 0;
};

#endif // PETOBSERVER_H


