{
  description = "Flake for C";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs?ref=nixos-unstable";
  };

  outputs = { self, nixpkgs }:
    let
      system = "x86_64-linux";
      pkgs = nixpkgs.legacyPackages."${system}";
    in
    {
      devShells.${system}.default = pkgs.mkShell {
        name = "c";

        nativeBuildInputs = with pkgs;[
          clang-tools
          clang

          gnumake
          cmake
          cmake-language-server
          gdb

          pkg-config
        ];

        buildInputs = with pkgs; [
          zlib
        ];

        env.LD_LIBRARY_PATH = pkgs.lib.makeLibraryPath [
          pkgs.stdenv.cc.cc.lib
          pkgs.zlib
        ];
      };
    };
}
