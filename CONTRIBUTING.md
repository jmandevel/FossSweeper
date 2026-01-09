<!--
SPDX-FileCopyrightText: 2022 Daniel Valcour <fosssweeper@gmail.com>

SPDX-License-Identifier: GPL-3.0-or-later
-->

# FossSweeper Contributing Guidelines

This file explains how to contribute to the FossSweeper project. For standards of behaviour, look at our [Code of Conduct](CODE_OF_CONDUCT.md).

## Forking

FossSweeper is released under the [GNU General Public License v3.0](https://www.gnu.org/licenses/gpl-3.0.en.html). This means that you are free to [fork this repository](https://docs.github.com/en/get-started/quickstart/fork-a-repo#fork-an-example-repository) and make your own alterations to FossSweeper and distribute your modified version. If you do this, you must also distribute your modified source code under the same license at the same places you distribute your version of the game.

## How to Report a Bug

Report bugs in the [issues board](https://www.github.com/jmandevel/FossSweeper/issues). [Create a new issue](https://docs.github.com/en/issues/tracking-your-work-with-issues/creating-an-issue) with the `Bug Report` template and fill out the form.

## How to Suggest a Feature

Suggest features in the [Ideas](https://www.github.com/jmandevel/FossSweeper/discussions/categories/ideas) category of the discussions board. When it is deemed that an adequate discussion has been completed, a thread in the issues board may be created to request the implementation of the feature.

## How to Ask a Question

Ask questions in the [Q&A](https://www.github.com/jmandevel/FossSweeper/discussions/categories/q&a) category of the discussions board.

## How to Contribute Code Changes

Browse the [issues board](https://www.github.com/jmandevel/FossSweeper/issues) to find an issue that interests you. If you want to work on an issue, say so by commenting in the issue thread. [Fork the dev branch](https://docs.github.com/en/get-started/quickstart/fork-a-repo#fork-an-example-repository) of the FossSweeper repository and [clone the fork](https://docs.github.com/en/repositories/creating-and-managing-repositories/cloning-a-repository) to your local machine. [Commit your changes](https://docs.github.com/en/desktop/contributing-and-collaborating-using-github-desktop/making-changes-in-a-branch/committing-and-reviewing-changes-to-your-project) locally and then [push them](https://docs.github.com/en/desktop/contributing-and-collaborating-using-github-desktop/making-changes-in-a-branch/pushing-changes-to-github) to your forked repository. When you are ready, go ahead and [make a pull request](https://docs.github.com/en/pull-requests/collaborating-with-pull-requests/proposing-changes-to-your-work-with-pull-requests/about-pull-requests) in the [FossSweeper pull requests board](https://github.com/jmandevel/FossSweeper/pulls).

Every time you push changes to GitHub, several tests will automatically run using [GitHub Actions](https://docs.github.com/en/actions). Before your pull request can be merged into FossSweeper, all of these tests must pass.

### Unit Tests with Catch2

Many aspects of FossSweeper are tested automatically using the [Catch2](https://github.com/catchorg/Catch2) unit testing framework. Depending on what code you added or modified, you may be required to add more unit tests or change existing ones. If you are not sure how you need to update the tests, ask for guidance in your pull request thread.

### Manual Integration Testing

Unit tests are not enough to catch everything that can go wrong with FossSweeper. Depending on what code you modify, you may be told that you need to run FossSweeper on one or more platforms to ensure that there are no visible bugs. You can emulate a different operating system than your own using [virtual machine](https://en.wikipedia.org/wiki/Virtual_machine) software such as [Virtual Box](https://www.virtualbox.org/). If you are using Windows, you can emulate a Linux distribution by using [WSL](https://en.wikipedia.org/wiki/Windows_Subsystem_for_Linux). Likewise, you can emulate Windows on a Linux distribution by using [WINE](https://www.winehq.org/). If you don't want to do this yourself, add the `help-needed` tag to your pull request and ask for someone else to do it for you.

### Licensing with REUSE

The FossSweeper project is a proponent of the [REUSE Specification](https://reuse.software/spec/). This means that all files in the repository must be adequately licensed for your fork to be considered [REUSE-compliant](https://reuse.software/tutorial/). If you have the [REUSE Tool](https://github.com/fsfe/reuse-tool) installed on your computer, you can check your fork to see if it is compliant using the bash command `reuse lint`.
