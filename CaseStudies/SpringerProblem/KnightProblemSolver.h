// =====================================================================================
// KnightProblemSolver.h
// =====================================================================================

#pragma once

// =====================================================================================
// defining 'operator<<' for solutions as a global function

template <typename T>
std::ostream& operator<< (std::ostream& os, const std::list<std::vector<Coordinate<T>>>& solutions) {

    int counter = 0;
    int width = (solutions.size() < 10) ? 1 : (solutions.size() < 100) ? 2 : 5;

    for (const std::vector<Coordinate<T>>& solution : solutions) {

        os << std::setw(width) << counter << ": ";

        for (const Coordinate<T>& coordinate : solution) {
            os << coordinate << " ";
        }
        counter++;
        os << std::endl;
    }

    return os;
}

// =====================================================================================
// defining 'KnightProblemSolver' template using 'inclusion model'

template <typename T, T HEIGHT, T WIDTH>
class KnightProblemSolver 
{
public:
    using Solution = std::vector<Coordinate<T>>;
    using ListSolutions = std::list<Solution>;

private:
    KnightProblemBoard<T, HEIGHT, WIDTH> m_board;        // chess board
    Solution                             m_current;      // solution being in construction
    ListSolutions                        m_solutions;    // list of found solutions
    T                                    m_moveNumber;   // number of last knight's move

public:
    // c'tor
    KnightProblemSolver() : m_moveNumber{ T{} } {}

public:
    // =================================================================================
    // public interface

    // getter/setter
    T getHeight() const noexcept { return HEIGHT; }
    T getWidth() const noexcept { return WIDTH; }

    ListSolutions getSolutions() const {
        return m_solutions;
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
        Coordinate<T> start{ HEIGHT - T{ 1 }, T{} };
        Logger<VerboseSolver>::log(std::cout, "   ... Starting sequential solver at ", start);
        int count = findMovesSequential(start);

        // stopwatch
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
        Logger<Verbose>::log(std::cout, "Elapsed time = ", duration, " [msecs]");

        assert(count == m_solutions.size());
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
        Coordinate<T> start{ HEIGHT - T{ 1 }, T{} };
        Logger<VerboseSolver>::log(std::cout, "   ... Starting parallel solver at ", start);
        int count = findMovesParallel(start, maxDepth);

        // stopwatch
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
        Logger<Verbose>::log(std::cout, "Elapsed time = ", duration, " [msecs]");

        assert(count == m_solutions.size());
        return static_cast<int> (m_solutions.size());
    }

    int countSolutions() {
        return static_cast<int> (m_solutions.size());
    }

    // functor notation needed for std::async
    ListSolutions operator()(const Coordinate<T> coord, int maxDepth) {

        Logger<VerboseSolver>::log(std::cout, "   ### Launching parallel solver at ", coord, ", maxDepth = ", maxDepth);
        Logger<Verbose>::logTID(std::cout);

        int count = findMovesParallel(coord, maxDepth);
        Logger<VerboseSolver>::log(std::cout, "   ### calculated  ", m_solutions.size(), " solutions !!!");

        assert(count == m_solutions.size());
        return m_solutions;
    }

private:
    // =================================================================================
    // internal helper methods

    // private helper - algorithm to solve the Knight's Tour problem sequentially
    int findMovesSequential(const Coordinate<T>& coord) {

        setKnightMoveAt(coord);
        m_current.push_back(coord);

        if (isSolution()) {
            // add found solution to the list of all solutions
            m_solutions.push_back(m_current);
        }
        else {
            // determine list of possible next moves
            std::vector<Coordinate<T>> nextMoves = nextKnightMoves(coord);

            // do next moves sequential
            for (const Coordinate<T>& move : nextMoves) {
                findMovesSequential(move);
            }
        }

        unsetKnightMoveAt(coord);
        m_current.pop_back();

        return static_cast<int> (m_solutions.size());
    }
    
    // private helper - algorithm to solve the Knight's Tour problem in parallel
    int findMovesParallel(const Coordinate<T>& coord, int maxDepth) {

        setKnightMoveAt(coord);
        m_current.push_back(coord);

        // determine list of possible next moves
        std::vector<Coordinate<T>> nextMoves = nextKnightMoves(coord);
        std::deque<std::future<ListSolutions>> futures;

        int count{};
        for (const Coordinate<T>& move : nextMoves) {

            KnightProblemSolver slaveSolver = *this;  // make a copy of the solver including the current board
            slaveSolver.clearSolutions();  // don't reuse solutions of current solver

            if (maxDepth > 0) {
                // do next moves parallel or ...
                std::future<ListSolutions> future = std::async(std::launch::async, std::move(slaveSolver), move, maxDepth - 1);
                futures.push_back(std::move(future));
            }
            else {
                // ... do next moves sequential
                Logger<VerboseSolver>::log(std::cout, "   ... Launching sequential solver at ", move);
                slaveSolver.findMovesSequential(move);
                count += slaveSolver.countSolutions();

                // need to copy all found solutions from slave solver to current solver
                ListSolutions solutions = slaveSolver.getSolutions();
                Logger<VerboseSolver>::log(std::cout, "   ... Calculated solutions from ", move, " => ", solutions.size());

                if (solutions.size() != 0) {
                    m_solutions.insert(std::end(m_solutions), std::begin(solutions), std::end(solutions));
                }
            }
        }

        // block async tasks, if any, and compute final result
        // (just use 'std::future' references to access non-copyable objects)
        for (std::future<ListSolutions>& future : futures) {

            ListSolutions partialSolutions = future.get();
            Logger<VerboseSolver>::log(std::cout, "   ... retrieved from Future: ", partialSolutions.size(), " solutions");

            if (partialSolutions.size() != 0) {
                m_solutions.insert(std::end(m_solutions), std::begin(partialSolutions), std::end(partialSolutions));
                count += static_cast<int> (partialSolutions.size());
            }
        }

        unsetKnightMoveAt(coord);
        m_current.pop_back();

        assert(count == m_solutions.size());
        return static_cast<int> (m_solutions.size());
    }

    // occupy square on the chess board
    void setKnightMoveAt(const Coordinate<T>& coord) {
        m_moveNumber++;
        m_board.at(coord) = m_moveNumber;
    }

    // release square on the chess board
    void unsetKnightMoveAt(const Coordinate<T>& coord) {
        m_moveNumber--;
        m_board.at(coord) = 0;
    }

    // compute list of next possible moves
    std::vector<Coordinate<T>> nextKnightMoves(const Coordinate<T>& coord) {
        std::vector<Coordinate<T>> list;

        if (Coordinate<T> tmp{ coord.fromOffset(2, 1) }; canMoveTo(tmp))
        {
            list.push_back(tmp);
        }
        if (Coordinate<T> tmp{ coord.fromOffset(1, 2) }; canMoveTo(tmp))
        {
            list.push_back(tmp);
        }
        if (Coordinate<T> tmp{ coord.fromOffset(-2, 1) }; canMoveTo(tmp))
        {
            list.push_back(tmp);
        }
        if (Coordinate<T> tmp{ coord.fromOffset(-1, 2) }; canMoveTo(tmp))
        {
            list.push_back(tmp);
        }
        if (Coordinate<T> tmp{ coord.fromOffset(2, -1) }; canMoveTo(tmp))
        {
            list.push_back(tmp);
        }
        if (Coordinate<T> tmp{ coord.fromOffset(1, -2) }; canMoveTo(tmp))
        {
            list.push_back(tmp);
        }
        if (Coordinate<T> tmp{ coord.fromOffset(-2, -1) }; canMoveTo(tmp))
        {
            list.push_back(tmp);
        }
        if (Coordinate<T> tmp{ coord.fromOffset(-1, -2) }; canMoveTo(tmp))
        {
            list.push_back(tmp);
        }

        return list;
    }

    // checks, whether coordinate does exist on the chess board
    bool inRange(const Coordinate<T>& coord) {
        return
            (coord.getRow() >= 0) && (coord.getRow() < HEIGHT) && 
            (coord.getCol() >= 0) && (coord.getCol() < WIDTH);
    }

    // checks, whether coordinate is valid and is still not taken
    bool canMoveTo(const Coordinate<T>& coord) {
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
