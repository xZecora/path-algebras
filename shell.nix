# default.nix
with import <nixpkgs> {};
stdenv.mkDerivation {
    name = "path-algebras"; # Probably put a more meaningful name here
    buildInputs = [ pkg-config libgcc ];
}
