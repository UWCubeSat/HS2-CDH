## Version Control and Branching

The default branch for this repository is main. Development is performed on feature branches, with the main branch reserved for stable, integrated code.

Direct commits to the main branch are not permitted. All changes must be proposed through a Pull Request, which is reviewed and validated before being merged. Feature branches should represent a single logical change and be named descriptively. Branches should be kept reasonably up to date with main to reduce merge conflicts.

## Pull Requests and Reviews

A Pull Request (PR) is the mechanism by which changes are proposed for inclusion in the main branch. Opening a PR begins the review process and signals that the change is ready for evaluation.

A PR may only be merged once the changes have been reviewed. At least two reviewer approvals are required, and the author of the PR may not approve their own changes. All review comments must be addressed or explicitly resolved prior to merging.

Pull Requests should be focused and limited in scope. Unrelated changes should be split into separate PRs. The PR description must clearly explain the purpose of the change, any relevant context, and any known limitations or follow-up work.

## Merge Strategy

All Pull Requests are merged using a squash merge.

A squash merge combines all commits in a Pull Request into a single commit on the main branch. This keeps the commit history clean, readable, and easy to audit. Each merged commit should represent one logical change. The squash commit message should clearly describe what was changed and why.

The main branch must always represent a stable, buildable state.

## Static Analysis and Style

C++ coding style is enforced using cpplint. All new and modified code must comply with the configured linting rules. We use C++ 14 for this codebase currently.

Suppressing a warning is permitted only when the warning is not applicable or would reduce clarity. Any suppression must be documented directly in the code with a clear justification.

## Documentation

Changes that affect behavior, usage, or public interfaces must be reflected in the appropriate documentation. Non-obvious design decisions should be explained through comments or documentation rather than left implicit in the implementation.

Please use Doxygen-style comments for all modified and newly added C++ headers and source files.

Documentation style requirements:

- Use block-style Doxygen comments (`/** ... */`) only.
- Do not use line-style Doxygen comments (`//!`) in `.hpp` or `.cpp` files.
- Every `.hpp` and `.cpp` file should start with a Doxygen file block containing a non-empty `@file` entry that includes the repository-relative path, for example:
	- `@file FlightComputer/Components/EventScheduler/EventScheduler.hpp`
- Public interfaces and non-trivial functions should include:
	- `@brief`
	- `@param[in]` / `@param[out]` / `@param[in,out]` as applicable
	- `@pre` and `@post` as applicable
	- `@return` for non-`void` functions
- Constructors and destructors should still include `@brief` and `@post` where appropriate.
- Constants and member fields should be documented with Doxygen block comments, not `@def` (reserve `@def` for preprocessor macros).

Example file header:

```cpp
/**
 * @file FlightComputer/Components/ImageProcessor/ImageCompressor/ImageCompressor.cpp
 * @author your-name
 * @brief cpp file for ImageCompressor component implementation class
 */
```

Example function documentation:

```cpp
/**
 * @brief Compress a raw image into a bitstream.
 * @param[in] opCode Opcode associated with this command invocation.
 * @param[in] cmdSeq Command sequence number for this invocation.
 * @param[in] input_file Path to the input .raw image file.
 * @param[in] output_dir Directory where the output .bin file is written.
 * @param[in] image_sample_len Number of samples available in the input buffer.
 * @pre input_file and output_dir are valid command arguments.
 * @post A command response is emitted indicating success or failure.
 */
```
