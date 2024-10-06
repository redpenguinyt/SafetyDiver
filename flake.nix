{
	description = "Flake for Playdate Development in Nix";

	inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";
    playdate-sdk.url = "github:RegularTetragon/playdate-sdk-flake";
  };

  outputs = { nixpkgs, playdate-sdk, ... }:
	  let
      system = "x86_64-linux";
      pkgs = nixpkgs.legacyPackages.${system};
      playdate-sdk-pkg = playdate-sdk.packages.${system}.default;
    in {
      devShells.${system}.default = pkgs.mkShell {
        packages = [ playdate-sdk-pkg pkgs.gcc-arm-embedded ];
        PLAYDATE_SDK_PATH = "${playdate-sdk-pkg}";
      };
    };
}
