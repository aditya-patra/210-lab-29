// Necessary Headers: map, array, list, iostream, fstream(more may need to be added, but these are the basic ones)

// Simulation function
// function parameter: pointer to current map
  // Livestock count can change through the following processes:
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
  // create file reader
  // read file to form map(each row should contain a)
  // call simulation function
  // repeat 60 times(300 years, 5 year interval)