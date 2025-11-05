// Necessary Headers: map, array, list, iostream, fstream(more may need to be added, but these are the basic ones)

// Simulation function
// function parameter: pointer to current map, pointer to number of available land segments
  // Iterate over farmers
    // Iterate over livestock species
      // For each livestock in current species, compare rand to chance of natural death of species to determine whether the animal dies
      // Keep track of number of dead animals and subtract from population at the end
    // Iterate over livestock species
      // For each livestock in current species, compare rand to chance of illness death of species to determine whether the animal dies
      // Keep track of number of dead animals and subtract from population at the end
    // compare rand to change of plague, if plague decrease livestock count by large percentage
    // Increase each livestock species by species-specific growth factor, make sure it doesn't exceed max population
  // For each piece of available land, use rand to choose farmer it goes to
    // Use rand to choose type of animal(if animal already in farm, add land to that list index)
  // Iterate over farmers
    // Recalculate value of each livestock species and update value list
    // If value less than 25, erase that index from all lists in that farmer
    // If total value of farmer is 0, erase farmer from map
  // - propogation: population increase is based on livestock cap and rate of growth varies by species
  // - natural death: chance of death varies between livestock species
  // - sudden illness: all livestock have equal chance of becoming ill
  // - plague: farmer loses most of a livestock species
  // After livestock change, program determines changes in land. If there is available land, it is randomly split between existing farmers
  // - when land is given to a farmer, there is an equal chance of it going to any livestock species or going to a new species
  // Value of each livestock for each farmer is then calculated.
  // If value of any livestock species is less than 25, farmer sells corresponding land as rent is more than earnings.
  // If a farmer loses all of his land, he goes bankrupt and is no longer included

// main function
  // instantiate map
  // set number of available land segments
  // create file reader
  // read file to form map(each row should contain a)
  // call simulation function
  // repeat 60 times(300 years, 5 year interval)