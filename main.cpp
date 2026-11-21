#include <iostream>
#include <filesystem>
#include <cstdlib>
#include <vector>
#include <podofo/podofo.h>

int main(int argc, char *argv[]) {
    // bool doc_st = true;
    if (argc <= 1) {
        std::cerr << "You are forgot about pdf files";
        return 0;
    }
    size_t mf_s = argc << 1;
    char **missed_files = static_cast<char**>(malloc(mf_s * sizeof(char*)));
    if (missed_files == nullptr) {
        std::cerr << "Missed files error (nullptr)";
        return 2;
    }
    int mfc = 0; // missed files count
    std::cout << "Your files:" << std::endl;
     for (int i = 1; i < argc; i++) {
        std::cout << argv[i] << std::endl;
         std::filesystem::path file_path(argv[i]);
         if (!std::filesystem::exists(file_path)) {
             std::cout << "File is missing: " << argv[i] << std::endl;
             missed_files[mfc++] = argv[i];
         }
     }
     if (mfc != 0) {
         std::cout << "Missed files: " << std::endl;
         for (int i = 0; i < mfc; i++) {
             std::cout << missed_files[i] << std::endl;
         }
         free(missed_files);
         return 1;
     }
    free(missed_files);
    //merging
    std::vector<PoDoFo::PdfMemDocument> docs;
    docs.reserve(size_t(argc-1));
    PoDoFo::PdfMemDocument merged_doc;
    for (int i = 1; i < argc; i++) {
        auto input = std::make_shared<PoDoFo::FileStreamDevice>(argv[i], PoDoFo::FileMode::Open);
        docs.emplace_back();
        docs.back().Load(input);
        merged_doc.GetPages().AppendDocumentPages(docs.back());
    }
    merged_doc.Save("merged.pdf");
    return 0;
}
