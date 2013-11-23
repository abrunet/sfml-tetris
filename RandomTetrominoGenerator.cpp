#include "RandomTetrominoGenerator.hpp"

#include <boost/assign/list_of.hpp>
#include <algorithm>
#include <ctime>

RandomTetrominoGenerator::RandomTetrominoGenerator() {
    rng.seed(std::time(0));
    appendNextBag();
}

RandomTetrominoGenerator::~RandomTetrominoGenerator() {}

TetrominoShape::Shape RandomTetrominoGenerator::pop() {
    TetrominoShape::Shape shape = bag.front();
    bag.pop_front();
    if (bag.empty()) {
        appendNextBag();
    }
    return shape;
}

TetrominoShape::Shape RandomTetrominoGenerator::peek() const {
    return bag.front();
}

void RandomTetrominoGenerator::appendNextBag() {
    std::vector<TetrominoShape::Shape> allPieces = 
            boost::assign::list_of(TetrominoShape::I)
                          (TetrominoShape::O)
                          (TetrominoShape::T)
                          (TetrominoShape::S)
                          (TetrominoShape::Z)
                          (TetrominoShape::J)
                          (TetrominoShape::L);
    shuffleBag(allPieces);
    bag.insert(bag.end(), allPieces.begin(), allPieces.end());
}

void RandomTetrominoGenerator::shuffleBag(std::vector<TetrominoShape::Shape>& shapes) {
    Generator rand(rng);
    std::random_shuffle(shapes.begin(), shapes.end(), rand);
}

