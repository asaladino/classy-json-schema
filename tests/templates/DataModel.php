<?php

namespace EthosApi\Data\Model;

use EthosApi\Data\Base\BaseModel;
/**
 * {{ description }}
 */
class {{ className }} {% if isDataModel %}extends BaseModel{% else %}{% endif %} {
    /**
     * Used for chain building a model.
     * @return Model|BaseModel
     */
    public static function builder()
    {
        return parent::builder();
    }
{% for value in properties %}{% if value/isArray %}
    /**
     * {{ value/description }}
     * @var {% if value/isString %}string{% else %}\EthosApi\Data\Model\{{ value/type }}{% endif %}[]
     */
    public ${{ value/variableName }};
{% else %}
    /**
     * {{ value/description }}
     * @var {% if value/isString %}string{% else %}\EthosApi\Data\Model\{{ value/type }}{% endif %}
     */
    public ${{ value/variableName }};
{% endif %}{% endfor %}
}