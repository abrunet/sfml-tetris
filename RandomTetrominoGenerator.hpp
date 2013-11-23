#ifndef RANDOM_TETROMINO_GENERATOR_HPP_
#define RANDOM_TETROMINO_GENERATOR_HPP_

#include "TetrominoShape.hpp"

#include <boost/random.hpp>
#include <functional>
#include <deque>
#include <vector>

class RandomTetrominoGenerator {
public:
    RandomTetrominoGenerator();
    virtual ~RandomTetrominoGenerator();

    TetrominoShape::Shape pop();
    TetrominoShape::Shape peek() const;

private:
    std::deque<TetrominoShape::Shape> bag;
    boost::mt19937 rng;

    void appendNextBag();
    void shuffleBag(std::vector<TetrominoShape::Shape>& bag);
};

struct Generator : std::unary_function<unsigned, unsigned> {
    boost::mt19937& state;
    unsigned operator()(unsigned i) {
        boost::uniform_int<> rng(0, i-1);
        return rng(state);
    }
    Generator(boost::mt19937& state) : state(state) {}
};

#endif // RANDOM_TETROMINO_GENERATOR_HPP_

