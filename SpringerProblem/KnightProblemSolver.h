// =====================================================================================
// KnightProblemSolver.h
// =====================================================================================

#pragma once

// =====================================================================================
// defining 'KnightProblemSolver' template using 'inclusion model'

using Solution = std::vector<Coordinate>;
using ListSolutions = std::list<Solution>;

std::ostream& operator<< (std::ostream& os, const ListSolutions& solutions) {

    int counter = 0;
    int width = (solutions.size() < 10) ? 1 : (solutions.size() < 100) ? 2 : 5;

    for (Solution s : solutions) {
        os << std::setw(width) << counter << ": ";

        for (Coordinate coord : s) {
            os << coord << " ";
        }
        counter++;
        os << std::endl;
    }

    return os;
}

template <int HEIGHT, int WIDTH>
class KnightProblemSolver 
{
private:
    KnightProblemBoard<HEIGHT, WIDTH> m_board;        // chess board
    ListSolutions                     m_solutions;    // list of found solutions
    Solution                          m_current;      // solution being in construction
    int                               m_moveNumber;   // number of last knight's move

public:
    // c'tor
    KnightProblemSolver() : m_moveNumber{ 0 } {}

public:
    // =================================================================================
    // public interface

    // getter/setter
    int getHeight() const { return HEIGHT; }
    int getWidth() const { return WIDTH; }

    ListSolutions getSolutions() {
        return { m_solutions };  // PeLo: Copy or not ?!?!?
    }

    void clearSolutions() {
        m_solutions.clear();
    }

    // public interface
    int findMovesSequential() {

        // reset data structures
        m_board.clearBoard();
        m_solutions.clear();
        m_current.clear();
        m_moveNumber = 0;

        // stopwatch
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

        // start at lower left corner            
        Coordinate start{ HEIGHT - 1, 0 };
        log(std::cout, "   ... starting seq solver at ", start);
        int count = findMovesSequential(start);

        // stopwatch
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
        log(std::cout, "Elapsed time = ", duration, " [msecs]");

        return static_cast<int> (m_solutions.size());
    }

    // find all solutions using thread pool (0 == seq, >= 1 par)
    int findMovesParallel(int maxDepth = 1) {

        // reset data structures
        m_board.clearBoard();
        m_solutions.clear();
        m_current.clear();
        m_moveNumber = 0;

        // stopwatch
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

        // start at lower left corner            
        Coordinate start{ HEIGHT - 1, 0 };
        log(std::cout, "   ... starting par solver at ", start);
        int count = findMovesParallel(start, maxDepth);

        // stopwatch
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
        log(std::cout, "Elapsed time = ", duration, " [msecs]");

        return static_cast<int> (m_solutions.size());
    }

    int countSolutions() {
        return static_cast<int> (m_solutions.size());
    }

    // functor notation needed for std::async
    ListSolutions operator()(const Coordinate& coord, int maxDepth) {

        log(std::cout, "   operator() ... launching par solver at ", coord, ", maxDepth = ", maxDepth);

        findMovesParallel(coord, maxDepth);
        log(std::cout, "   operator() ... return list with ", m_solutions.size(), " solutions !!!");

        return m_solutions;
    }

private:
    // =================================================================================
    // internal helper methods

    // private helper - algorithm to solve the Knight's Tour problem sequentially
    int findMovesSequential(const Coordinate& coord) {
        setKnightMoveAt(coord);
        m_current.push_back(coord);

        if (isSolution())
        {
            // need a copy of the current solution
            Solution copy{ m_current };

            // add found solution to the list of all solutions
            m_solutions.push_back(copy);
        }
        else
        {
            // determine list of possible next moves
            std::vector<Coordinate> nextMoves = nextKnightMoves(coord);

            // do next moves sequential
            for (Coordinate move : nextMoves) {
                findMovesSequential(move);
            }
        }

        unsetKnightMoveAt(coord);
        m_current.pop_back();

        return static_cast<int> (m_solutions.size());
    }
    
    // private helper - algorithm to solve the Knight's Tour problem in parallel
    int findMovesParallel(const Coordinate& coord, int maxDepth) {

        setKnightMoveAt(coord);
        m_current.push_back(coord);

        // determine list of possible next moves
        std::vector<Coordinate> nextMoves = nextKnightMoves(coord);
        std::deque<std::future<ListSolutions>> futures;

        int result{};

        log(std::cout, "   ... next possible moves: ", nextMoves.size());

        for (Coordinate move : nextMoves) {

            // make a copy of the solver including the current board
            KnightProblemSolver slaveSolver = *this;

            // DON'T REUSE SOLUTINS ... DAS IST SHITTY
            slaveSolver.clearSolutions();

            if (maxDepth > 0) {
                // do next moves parallel or ...
                std::future<ListSolutions> future = std::async(std::launch::async, std::move(slaveSolver), move, maxDepth - 1);
                futures.push_back(std::move(future));
            }
            else {
                // ... do next moves sequential
                log(std::cout, "   ... launching seq solver at ", move);
                slaveSolver.findMovesSequential(move);
                result += slaveSolver.countSolutions();

                // need to copy all found solutions from slave solver to current solver
                ListSolutions solutions = slaveSolver.getSolutions();
                log(std::cout, "   ...   calculated solutions FROM ", move, " => ", solutions.size());

                if (solutions.size() != 0) {
                    m_solutions.insert(std::end(m_solutions), std::begin(solutions), std::end(solutions));
                }
            }
        }

        // block async tasks, if any, now and compute final result
        // (just use references to access non-copyable objects)
        for (std::future<ListSolutions>& future : futures)
        {
            ListSolutions partialSolutions = future.get();
            log(std::cout, "   ...   RETRIEVED from future: List of length ", partialSolutions.size());

            if (partialSolutions.size() != 0) {
                m_solutions.insert(std::end(m_solutions), std::begin(partialSolutions), std::end(partialSolutions));
                result += static_cast<int> (partialSolutions.size());
            }
        }

        unsetKnightMoveAt(coord);
        m_current.pop_back();

        return static_cast<int> (m_solutions.size());
        // return result;
    }

    // occupy square on the chess board
    void setKnightMoveAt(const Coordinate& coord) {
        m_moveNumber++;
        m_board.at(coord) = m_moveNumber;
    }

    // release square on the chess board
    void unsetKnightMoveAt(const Coordinate& coord) {
        m_moveNumber--;
        m_board.at(coord) = 0;
    }

    // compute list of next possible moves
    std::vector<Coordinate> nextKnightMoves(const Coordinate& coord) {
        std::vector<Coordinate> result;

        if (Coordinate tmp{ coord.fromOffset(2, 1) }; canMoveTo(tmp))
        {
            result.push_back(tmp);
        }
        if (Coordinate tmp{ coord.fromOffset(1, 2) }; canMoveTo(tmp))
        {
            result.push_back(tmp);
        }
        if (Coordinate tmp{ coord.fromOffset(-2, 1) }; canMoveTo(tmp))
        {
            result.push_back(tmp);
        }
        if (Coordinate tmp{ coord.fromOffset(-1, 2) }; canMoveTo(tmp))
        {
            result.push_back(tmp);
        }
        if (Coordinate tmp{ coord.fromOffset(2, -1) }; canMoveTo(tmp))
        {
            result.push_back(tmp);
        }
        if (Coordinate tmp{ coord.fromOffset(1, -2) }; canMoveTo(tmp))
        {
            result.push_back(tmp);
        }
        if (Coordinate tmp{ coord.fromOffset(-2, -1) }; canMoveTo(tmp))
        {
            result.push_back(tmp);
        }
        if (Coordinate tmp{ coord.fromOffset(-1, -2) }; canMoveTo(tmp))
        {
            result.push_back(tmp);
        }

        return result;
    }

    // checks, whether coordinate does exist on the chess board
    bool inRange(const Coordinate& coord) {
        return
            (coord.getRow() >= 0) && (coord.getRow() < HEIGHT) && 
            (coord.getCol() >= 0) && (coord.getCol() < WIDTH);
    }

    // checks, whether coordinate is valid and is still not taken
    bool canMoveTo(const Coordinate& coord) {
        return inRange(coord) && (m_board.at(coord) <= 0);
    }

    // verifies, whether current list of moves is a solution
    bool isSolution() {
        return m_moveNumber >= HEIGHT * WIDTH;
    }
};

// =====================================================================================
// End-of-File
// =====================================================================================
