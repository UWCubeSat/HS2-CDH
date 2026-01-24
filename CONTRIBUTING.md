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

C++ coding style is enforced using cpplint. All new and modified code must comply with the configured linting rules.

Suppressing a warning is permitted only when the warning is not applicable or would reduce clarity. Any suppression must be documented directly in the code with a clear justification.

## Documentation

Changes that affect behavior, usage, or public interfaces must be reflected in the appropriate documentation. Non-obvious design decisions should be explained through comments or documentation rather than left implicit in the implementation.
