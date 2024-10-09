{ pkgs, ... }: {
  channel = "stable-23.11";
  packages = [
    pkgs.clang
    pkgs.cmake
    pkgs.gnumake42
  ];

  idx = {
    extensions = [
      # "vscodevim.vim"
      "EditorConfig.EditorConfig"
    ];
  };
}
