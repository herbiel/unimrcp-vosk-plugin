#include "base/kaldi-common.h"
#include "util/common-utils.h"
#include "fstext/fstext-lib.h"
#include "fstext/fstext-utils.h"
#include "decoder/lattice-faster-decoder.h"
#include "feat/feature-mfcc.h"
#include "lat/kaldi-lattice.h"
#include "lat/word-align-lattice.h"
#include "nnet3/am-nnet-simple.h"
#include "nnet3/nnet-am-decodable-simple.h"
#include "nnet3/nnet-utils.h"

#include "model.h"

using namespace kaldi;

class KaldiRecognizer {
    public:
        KaldiRecognizer(Model &model);
        ~KaldiRecognizer();
        void CleanUp();
        bool AcceptWaveform(const char *data, int len);
        std::string Result();
        std::string PartialResult();

    private:
        Model &model_;
        SingleUtteranceNnet3Decoder *decoder_;

        OnlineNnet2FeaturePipelineInfo *feature_info_;
        OnlineNnet2FeaturePipeline *feature_pipeline_;
        OnlineSilenceWeighting *silence_weighting_;

        bool input_finalized_;
};
