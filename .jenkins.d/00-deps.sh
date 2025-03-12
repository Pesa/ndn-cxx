#!/usr/bin/env bash
set -eo pipefail

APT_PKGS=(
    dpkg-dev
    g++
    libboost-chrono-dev
    libboost-date-time-dev
    libboost-dev
    libboost-log-dev
    libboost-program-options-dev
    libboost-stacktrace-dev
    libboost-test-dev
    libboost-thread-dev
    libsqlite3-dev
    libssl-dev
    pkg-config
    python3
)
FORMULAE=(boost openssl pkgconf)
case $JOB_NAME in
    *code-coverage)
        APT_PKGS+=(lcov python3-venv)
        PIPX=pipx
        ;;
    *Docs)
        APT_PKGS+=(doxygen graphviz python3-venv)
        FORMULAE+=(doxygen graphviz pipx)
        PIPX=pipx
        ;;
esac

set -x

if [[ $ID == macos ]]; then
    export HOMEBREW_NO_ENV_HINTS=1
    if [[ -n $GITHUB_ACTIONS ]]; then
        export HOMEBREW_NO_INSTALLED_DEPENDENTS_CHECK=1
    fi
    brew update
    brew install --formula "${FORMULAE[@]}"
elif [[ $ID_LIKE == *debian* ]]; then
    sudo apt-get update -qq
    sudo apt-get install -qy --no-install-recommends "${APT_PKGS[@]}"
    if [[ -n $PIPX && -z $GITHUB_ACTIONS ]]; then
        curl -fLOSs --output-dir "$CACHE_DIR" 'https://github.com/pypa/pipx/releases/download/1.7.1/pipx.pyz'
        PIPX="python3 $CACHE_DIR/pipx.pyz"
    fi
elif [[ $ID_LIKE == *fedora* ]]; then
    sudo dnf install -y gcc-c++ libasan lld pkgconf-pkg-config python3 \
                        boost-devel openssl-devel sqlite-devel
fi

case $JOB_NAME in
    *code-coverage)
        $PIPX install 'gcovr~=5.2'
        ;;
    *Docs)
        $PIPX install 'sphinx~=8.0'
        $PIPX inject sphinx sphinxcontrib-doxylink
        ;;
esac
