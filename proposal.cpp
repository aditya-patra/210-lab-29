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
    // If value less than 25, store index in temp variable, check temp next iteration, iterate through each list and delete index
    // If total value of farmer is 0, erase farmer from map

// main function
  // instantiate map
  // set number of available land segments
  // create file reader
  // read file to form map(each row should contain a)
  // call simulation function
  // repeat 60 times(300 years, 5 year interval)